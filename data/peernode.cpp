#include "peernode.h"

PeerNode::PeerNode(QObject *parent) :
    QObject(parent)
{
}

QTcpSocket *PeerNode::getSocket() {
    return tcpSocket;
}

void PeerNode::setSocket(QTcpSocket *socket) {
    this->tcpSocket = socket;
}

QHostAddress PeerNode::getAddress() {
    return address;
}

void PeerNode::setAddress(QHostAddress address) {
    this->address = address;
}

int PeerNode::getId() {
    return id;
}

void PeerNode::setId(int id) {
    this->id = id;
}

bool PeerNode::operator == (PeerNode *other) {
    return this->id == other->id;
}
