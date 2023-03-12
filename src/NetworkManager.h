//
// Created by Utilizador on 12/03/2023.
//
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Station.h"
#include "Network.h"
#include <set>

using namepsace std;

class NetworkManager {
public:
    NetworkManager();
    void readFiles();
private:
    Graph railway;
    set<Station> stations;
    set<Network> network;
};

#endif //NETWORKMANAGER_H
