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

class NetworkManager : public Graph {
public:
    NetworkManager();
    void readFiles();

    int indexA(string a);
    int indexB(string a);
    Graph get_railway();
    unordered_map<std::string,int> get_stations_code_reversed();
    std::unordered_map<int,std::string> get_stations_code();

private:
    Graph railway;
    set<Station> stationsSet;
    set<Network> networkSet;
    unordered_map<std::string,int> stations_code_reverse;
    unordered_map<int,std::string> stations_code;

};

#endif //NETWORKMANAGER_H
