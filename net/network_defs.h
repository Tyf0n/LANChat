#ifndef NETWORK_DEFS_H
#define NETWORK_DEFS_H

#include <QtGlobal>

//Defines constants for networking

namespace LANChatNetDefs {
    //Port used for UDP for discovery of peers
    const int updPort = 2727;

    //Port used for TCP communications
    const int tcpPort = 2728;

    //Number of milliseconds to wait in between sending UDP packets
    const int finderDelay = 1000;

    //Peer finder protocol version
    const quint16 finderVersion = 1;
}

#endif // NETWORK_DEFS_H
