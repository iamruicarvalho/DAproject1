//
// Created by Bernardo Pinto on 06/03/2023.
//

#include <fstream>
#include <sstream>
#include <unordered_map>
#include "codigo/include/network.h"
#include "codigo/include/station.h"

Network::Network(){
    for (auto x:stations){
        network.addVertex(x.first);
    }
}

void Network::set_network(Graph network) {
    this->network=network;
}

void Network::read_network() {
    int network_count=0;
    std::fstream fin;
    fin.open("../files_to_read/airlines.csv", std::ios::in);
    std::vector<std::string> row;
    std::string line, word, temp;
    while(!fin.eof()){
        row.clear();
        getline(fin,line);
        if(line== "") break;
        std::stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        if (network_count==0){
            network_count++;
            continue;
        }
        int code_StationA =
    }
}