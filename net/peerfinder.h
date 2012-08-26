#ifndef PEERFINDER_H
#define PEERFINDER_H

#include <QObject>

#include "../data/peernode.h"

class QUdpSocket;
class QTimerEvent;

class PeerFinder : public QObject
{
    Q_OBJECT
public:
    explicit PeerFinder(QObject *parent = 0);

protected:
    /**
      Unique local identifier for this node
      This implementation doesn't work with more than 65,535 nodes.
      */
    quint16 localId;

    QUdpSocket *socket;

    /**
      Timer for sending out datagrams
      */
    int sendTimerId;
    
    void timerEvent(QTimerEvent * e);

    /**
      Send out a datagram identifying this computer
      */
    void send();

signals:

    /**
      Emitted when a packet is received indicating that a peer node exists.
      This is not emitted for packets from this node.
      This is emitted multiple times for each peer node with a newly allocated node object on the heap.
      (Confound these private copy constructors! They drive me to use pointers.)

      Receivers can ignore this signal if they already know about this peer.
      (The == operator can be used to compare the IDs of two nodes).

      If the program structure ensures that only one object is connected to this signal,
      the one receiver should delete this pointer.
      */
    void nodeSeen(PeerNode *node);
    
public slots:
    
    /**
      Start sending out and listening for packets
      */
    void start();

    /**
      Pause the sending out of and listening for packets.
      After this is called, start() may be called to resume it.
      */
    void pause();

private slots:
    /**
      Connected to readyRead() of the UDP socket
      */
    void read();
};

#endif // PEERFINDER_H
