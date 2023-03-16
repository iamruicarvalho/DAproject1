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
    std::fstream stationsFile;
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
        getline(iss, line, ',');

        Station station(name, district, municipality, township, line);
        stationsSet.push_back(station);
        /*
        if (!(stations_code_reverse.count(row[0]))) {
            i++;
            stations_code_reverse[row[0]] = i;
            stations_code[i] = row[0];
            network.addVertex(i);
        }
        */
        stationsFile.close();
        cout << "There are" << temp.size() " stations!" << endl;
    }


    // read network.csv
    int network_count=0;
    std::fstream networkFile;
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
        getline(iss, statioB, ',');
        getline(iss, capacity, ',');
        getline(iss, service, ',');

        Network network(stationA, stationB, capacity, service);
        networkSet.push_back(network);
        }
        
        int code_StationA = stations_code_reverse[row[0]];
        int code_StationB = stations_code_reverse[row[1]];
        network.addEdge(code_StationA,code_StationB,std::stod(row[2]));
    }
}


