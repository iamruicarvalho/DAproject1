//
// Created by Utilizador on 12/03/2023.
//
#include "NetworkManager.h"

/*
Network::Network(){
    read_stations();
    read_connections();
}

Graph Network::get_network() {
    return network;
}

std::unordered_map<std::string,int> Network::get_stations_code_reversed() {
    return stations_code_reverse;
}

std::unordered_map<int,std::string> Network::get_stations_code(){
    return stations_code;
}

void Network::read_stations() {
    int station_count=0;
    std::fstream fin;
    fin.open("../resources/stations.csv", std::ios::in);
    std::vector<std::string> row;
    std::string line, word, temp;
    int i=0;
    while(!fin.eof()){
        row.clear();
        getline(fin,line);
        if(line== "") break;
        std::stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        if (station_count==0){
            station_count++;
            continue;
        }
        if(!(stations_code_reverse.count(row[0]))) {
            i++;
            stations_code_reverse[row[0]] = i;
            stations_code[i] = row[0];
            network.addVertex(i);
        }
    }
}

void Network::read_connections() {
    int network_count=0;
    std::fstream fin;
    fin.open("../resources/network.csv", std::ios::in);
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
        int code_StationA = stations_code_reverse[row[0]];
        int code_StationB = stations_code_reverse[row[1]];
        network.addEdge(code_StationA,code_StationB,std::stod(row[2]));
    }
}*/
