//
// Created by Bernardo Pinto on 06/03/2023.
//

#ifndef PROJETO1_NETWORK_H
#define PROJETO1_NETWORK_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Graph.h"

class Network{
public:
    Network();
    void read_connections();
    void read_stations();
    Graph get_network();
    std::unordered_map<int,std::string> get_stations_code();
    std::unordered_map<std::string,int> get_stations_code_reversed();
private:
    Graph network;
    std::unordered_map<int,std::string> stations_code;
    std::unordered_map<std::string,int> stations_code_reverse;
};

#endif //PROJETO1_NETWORK_H
