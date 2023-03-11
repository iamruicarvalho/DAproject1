//
// Created by Bernardo Pinto on 06/03/2023.
//

#ifndef PROJETO1_NETWORK_H
#define PROJETO1_NETWORK_H

#include <string>
#include <vector>
#include "codigo/data_structures/Graph.h"
#include "station.h"

class Network{
public:
    Network();
    void read_network();
    void set_network(Graph network);
private:
    Graph network;
    std::unordered_map<int,std::string> stations = Station().get_stations_code();
};

#endif //PROJETO1_NETWORK_H
