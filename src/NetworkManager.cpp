//
// Created by Utilizador on 12/03/2023.
//
#include <iostream>
#include "NetworkManager.h"

using namespace std;

void NetworkManager::readFiles() {
    cout << "Loading files..." << endl;

    // read stations.csv
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


    // read network.csv
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
}


