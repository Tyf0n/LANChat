#include "peerfinder.h"
#include "network_defs.h"

#include <QtNetwork/QUdpSocket>
#include <QTimerEvent>
#include <QByteArray>
#include <QBuffer>
#include <QDataStream>

/*
  Peer finder packet format:
    quint16 version number
    quint16 peer ID
  */

PeerFinder::PeerFinder(QObject *parent) :
    QObject(parent)
{
    //Assign a random local ID
    int tempId = qrand();
    do {
        tempId = qrand();
    } while(tempId < 0 || tempId > 65535);
    localId = tempId;

    qDebug() << "Node finder starting up. ID" << localId;

    socket = new QUdpSocket(this);
    socket->bind(LANChatNetDefs::updPort, QUdpSocket::ShareAddress);

    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void PeerFinder::read() {
    QByteArray input;
    input.resize(socket->pendingDatagramSize());

    QHostAddress senderAddress;
    socket->readDatagram(input.data(), input.size(), &senderAddress);

    for(int i = 0, max = input.size(); i < max; i++) {
        qDebug() << "input["<<i<<"] = " << (int) input[i];
    }

    QBuffer buffer(&input);
    buffer.open(QIODevice::ReadOnly);
    QDataStream stream(&buffer);


    quint16 remoteId;
    stream >> remoteId;

//    if(remoteVersion != LANChatNetDefs::finderVersion) {
//        qWarning() << "Received finder datagram from a client with a different version ("<<remoteVersion<<"). Ignoring.";
//        return;
//    }

    if(remoteId != localId) {
        qDebug() << "Got packet from" << remoteId << "address" << senderAddress.toString();
        PeerNode *node = new PeerNode(this);
        node->setId(remoteId);
        node->setAddress(senderAddress);

        emit nodeSeen(node);
    }
}

void PeerFinder::send() {
    QByteArray output;
    QBuffer buffer(&output);
    buffer.open(QIODevice::ReadWrite);
    QDataStream stream(&buffer);

    stream << localId;

    qDebug() << "Sending" << output.size() << "bytes.";
    for(int i = 0, max = output.size(); i < max; i++) {
        qDebug() << "output["<<i<<"] = " << (int) output[i];
    }

    if(output.size() > 512) {
        qWarning() << "Trying to send a datagram" << output.size() << "bytes long. This may cause problems.";
    }

    socket->writeDatagram(output, QHostAddress::Broadcast, LANChatNetDefs::updPort);
}

void PeerFinder::timerEvent(QTimerEvent * e) {
    if(e->timerId() == sendTimerId) {
        send();
    }
}

void PeerFinder::start() {
    sendTimerId = startTimer(LANChatNetDefs::finderDelay);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void PeerFinder::pause() {
    killTimer(sendTimerId);
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}
