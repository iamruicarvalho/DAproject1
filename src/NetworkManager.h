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
<<<<<<< HEAD
    void readFiles();



private:
    Graph railway;
    set<Station> stationsSet;
    set<Network> networkSet;
    unordered_map<int, string> stations_code;
    unordered_map<string, int> stations_code_reverse;
=======
    unordered_map<std::string,int> get_stations_code_reversed();
    std::unordered_map<int,std::string>get_stations_code();
    void read_stations();
    int indexA(string a);
    int indexB(string a);
    void read_connections();
    Graph get_railway();
private:
    Graph railway;
    set<Station> stations;
    set<Network> network;
    unordered_map<std::string,int> stations_code_reverse;
    unordered_map<int,std::string> stations_code;
>>>>>>> 401acb91568fcfb6a7147f61ddb30eb248914b6f
};

#endif //NETWORKMANAGER_H
