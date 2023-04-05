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
    int max_trains(string source, string target);
    int max_trains_with_blocks(string source, string target);
    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    void testAndVisitWithBlocks(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool augmentingPath(Vertex *s, Vertex *t);
    bool augmentingPathWithBlocks(Vertex *s, Vertex *t);
    double minResidual(Vertex *s, Vertex *t);
    void update(Vertex *s, Vertex *t, double f);
    pair<int,pair<string,string>> max_of_max_trains();
    bool set_block(string A, string B);
    bool remove_block(string A, string B);
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
    vector<pair<Edge*,Edge*>> edgesBlocked;

};

#endif //NETWORKMANAGER_H
