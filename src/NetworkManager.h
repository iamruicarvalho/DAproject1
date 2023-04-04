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
#include <list>

using namespace std;

class NetworkManager : public Graph {
public:
    NetworkManager();
    void readFiles();

    int indexA(string a);
    int indexB(string a);
    unordered_map<std::string,int> get_stations_code_reversed();
    std::unordered_map<int,std::string> get_stations_code();
    int max_trains(string source, string target,int result_final, bool changed);
    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool augmentingPath(Vertex *s, Vertex *t);
    double minResidual(Vertex *s, Vertex *t);
    void update(Vertex *s, Vertex *t, double f);
    int max_of_max_trains();
    set<int> returnBlockedStations(const string& line);
    void setBlockLine(const string& blockline);
    void setBlockStation(const string& blockline);
    void max_of_max_trains_with_block(string blockLine);
    void trainManagementByMunicipality(int k);
    void trainManagementByDistrict(int k);
    void trainManagementByTownship(int k);

private:
    set<Station> stationsSet;
    set<Network> networkSet;
    unordered_map<std::string,int> stations_code_reverse;
    unordered_map<int,std::string> stations_code;
    unordered_map<std:: string, int> network_code_reverse;


};

#endif //NETWORKMANAGER_H
