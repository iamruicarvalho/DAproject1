//
// Created by Utilizador on 12/03/2023.
//
#include "NetworkManager.h"


NetworkManager::NetworkManager(){
    read_stations();
    read_connections();
}

Graph NetworkManager::get_railway() {
    return railway;
}

std::unordered_map<std::string,int> NetworkManager::get_stations_code_reversed() {
    return stations_code_reverse;
}

std::unordered_map<int,std::string> NetworkManager::get_stations_code(){
    return stations_code;
}

void NetworkManager::read_stations() {
    int station_count=0;
    std::fstream fin;
    fin.open("../resources/stations.csv", std::ios::in);
    std::vector<std::string> row;
    std::string line, word, temp;
    int i=0;
    while(!fin.eof()){
        row.clear();
        getline(fin,line);
        if(line.empty()) break;
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
            railway.addVertex(i);
        }
    }
}

void NetworkManager::read_connections() {
    int network_count=0;
    std::fstream fin;
    fin.open("../resources/network.csv", std::ios::in);
    std::vector<std::string> row;
    std::string line, word, temp;
    while(!fin.eof()){
        row.clear();
        getline(fin,line);
        if(line.empty()) break;
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
        railway.addEdge(code_StationA,code_StationB,std::stod(row[2]));
    }
}
