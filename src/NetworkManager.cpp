//
// Created by Utilizador on 12/03/2023.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "NetworkManager.h"

using namespace std;

void NetworkManager::readFiles() {
    cout << "Loading files..." << endl;

    // read stations.csv
    int station_count = 0;
    std::ifstream stationsFile;
    stationsFile.open("../resources/stations.csv");
    if (!stationsFile.is_open()){
        cout << "File not found\n";
        return;
    }

    std::string line;
    //int i=0;
    getline(stationsFile, line)
    while (getline(stationsFile, line)) {
        //row.clear();
        string name, district, municipality, township, line;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        iss >> line;

        Station station(name, district, municipality, township, line);
        stationsSet.push_back(station);
        /*
        if (!(stations_code_reverse.count(row[0]))) {
            i++;
            stations_code_reverse[row[0]] = i;
            stations_code[i] = row[0];
            railway.addVertex(i);
        }*/
    }
    stationsFile.close();
    cout << "There are" << stationsSet.size() " stations!" << endl;


    // read network.csv
    int network_count = 0;
    std::ifstream networkFile;
    networkFile.open("../resources/network.csv");
    if (!networkFile.is_open()){
        cout << "File not found\n";
        return;
    }

    //int i=0;
    getline(networkFile, line)
    while (getline(networkFile, line)) {
        //row.clear();
        string stationA, stationB, capacity, service;
        istringstream iss(line);
        getline(iss, stationA, ',');
        getline(iss, stationB, ',');
        getline(iss, capacity, ',');
        iss >> service;

        Network network(stationA, stationB, capacity, service);
        networkSet.push_back(network);
        railway.addEdge(stationA, stationB, capacity);
    }
    networkFile.close();
    cout << "In all, there are" << networkSet.size() " possible connections in the provided railway network!" << endl;

    int code_StationA = stations_code_reverse[row[0]];
    int code_StationB = stations_code_reverse[row[1]];
    railway.addEdge(code_StationA,code_StationB,std::stod(row[2]));
}


int NetworkManager:: indexA(string a){
    auto it = stations_code_reverse.find(a);
    return it->second;
}
int NetworkManager:: indexB(string a){
    auto it = stations_code_reverse.find(a);
    return it->second;
}

