//
// Created by Utilizador on 12/03/2023.
//
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Station.h"
#include "Network.h"
#include <string>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

class NetworkManager {
public:
    NetworkManager();
    unordered_map<std::string,int> get_stations_code_reversed();
    std::unordered_map<int,std::string>get_stations_code();
    void read_stations();
    void read_connections();
    Graph get_railway();
private:
    Graph railway;
    set<Station> stations;
    set<Network> network;
    unordered_map<std::string,int> stations_code_reverse;
    unordered_map<int,std::string> stations_code;
};

#endif //NETWORKMANAGER_H
