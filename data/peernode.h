#ifndef PEERNODE_H
#define PEERNODE_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

/**
  Stores data for a peer on the network, including its IP address, unique ID, and TCP socket
  */
class PeerNode : public QObject
{
    Q_OBJECT
public:
    explicit PeerNode(QObject *parent = 0);

    void setAddress(QHostAddress address);
    void setId(int id);
    
    QHostAddress getAddress();
    QTcpSocket *getSocket();
    int getId();

    void setSocket(QTcpSocket *socket);


    //Operators

    bool operator == (PeerNode *other);

protected:

    QTcpSocket *tcpSocket;

    quint16 id;

    QHostAddress address;

signals:
    
public slots:
    
};

#endif // PEERNODE_H
