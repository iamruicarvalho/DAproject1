//
// Created by Utilizador on 12/03/2023.
//
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Station.h"
#include "Network.h"
#include <set>

using namespace std;

class NetworkManager : public Graph {
public:
    NetworkManager();
    void readFiles();



private:
    Graph railway;
    set<Station> stationsSet;
    set<Network> networkSet;
    unordered_map<int, string> stations_code;
    unordered_map<string, int> stations_code_reverse;
};

#endif //NETWORKMANAGER_H
