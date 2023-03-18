//
// Created by Utilizador on 12/03/2023.
//
#include <iostream>
#include "NetworkManager.h"

using namespace std;

NetworkManager::NetworkManager() {

}

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
    int i=0;
    getline(stationsFile, line);
    while (getline(stationsFile, line)) {
        //line.clear();
        string name, district, municipality, township, line;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        getline(iss, line, ',');
        Station station(name, district, municipality, township, line);
        stations.push_back(station);
        if (!(stations_code_reverse.count(name)) && name != "NAME") {
            i++;
            stations_code_reverse[name] = i;
            stations_code[i] = name;
            railway.addVertex(i);
        }
    }
    stationsFile.close();
    cout << "There are" << stations.size() <<" stations!" << endl;


    // read network.csv
    int network_count=0;
    std::fstream networkFile;
    networkFile.open("../resources/network.csv");
    if (!networkFile.is_open()){
        cout << "File not found\n";
        return;
    }

    //int i=0;
    getline(networkFile, line);
    while (getline(networkFile, line)) {
        //row.clear();
        string stationA, stationB, capacity, service;
        istringstream iss(line);
        getline(iss, stationA, ',');
        getline(iss, stationB, ',');
        getline(iss, capacity, ',');
        getline(iss, service, ',');

        Network net(stationA, stationB, stoi(capacity), service);
        network.push_back(net);

        int code_StationA = stations_code_reverse[stationA];
        int code_StationB = stations_code_reverse[stationB];
        railway.addEdge(code_StationA,code_StationB,std::stod(capacity));
    }
    networkFile.close();
    cout << "In all, there are" << network.size() << " possible connections in the provided railway network!" << endl;
}


int NetworkManager:: indexA(string a){
    auto it = stations_code_reverse.find(a);
    return it->second;
}
int NetworkManager:: indexB(string a){
    auto it = stations_code_reverse.find(a);
    return it->second;
}


//2.1

bool NetworkManager::Path(int source,int target){
    for(auto vertex:vertexSet) {
        vertex->setVisited(false);
        vertex->setPath(nullptr);
    }
    std::queue<Vertex*> q;
    Vertex* starting= findVertex(source);
    q.push(starting);
    while(!q.empty()){
        Vertex* that=q.front();
        q.pop();
        for(auto edge:that->getAdj()){
            edge->setSelected(false);
            Vertex* dest= edge->getDest();
            if(!dest->isVisited() && edge->getWeight()-edge->getFlow() > 0){
                dest->setVisited(true);
                dest->setPath(edge);
                q.push(dest);
            }
        }
        for(auto edge:that->getIncoming()){
            Vertex* incoming=edge->getOrig();
            if(!incoming->isVisited() && edge->getFlow()>0){
                incoming->setVisited(true);
                Edge* reversed = new Edge(edge->getDest(),edge->getOrig(),edge->getWeight());
                edge->setReverse(reversed);
                incoming->setPath(edge);
                q.push(incoming);
            }
        }
    }
    return findVertex(target)->isVisited();
}

int NetworkManager::minResidual(int source,int target) {
    int disponivel;
    Vertex* end = findVertex(target);
    Vertex* incoming = end->getPath()->getOrig();
    int minFlow = end->getPath()->getWeight() - incoming->getPath()->getFlow();
    while(incoming->getId()!=source){
        if(incoming->getPath()->getReverse() == nullptr) {
            disponivel = incoming->getPath()->getWeight() - incoming->getPath()->getFlow();
            minFlow = std::min(minFlow, disponivel);
            incoming = incoming->getPath()->getOrig();
        }
        else {
            disponivel = incoming->getPath()->getFlow();
            minFlow = std::min(minFlow, disponivel);
            incoming = incoming->getPath()->getDest();
        }
    }
    return minFlow;
}

void NetworkManager::Update(int flow, int source, int target, int& result) {
    Vertex* u = findVertex(target);
    while(u!= findVertex(source)){
        auto edge = u->getPath();
        if (edge->getReverse()==nullptr){
            edge->setFlow(edge->getFlow()+flow);
            result+=flow;
            u=edge->getOrig();
        }
        else{
            edge->setFlow(edge->getFlow()-flow);
            result-=flow;
            u=edge->getDest();
            edge->setReverse(nullptr);
        }
    }
}

int NetworkManager::max_trains(string A, string B, bool changed) {
    int source = stations_code_reverse[A];
    int target = stations_code_reverse[B];
    int result=0;
    for(auto vertex:vertexSet){
        for(auto edge:vertex->getAdj()){
            edge->setFlow(0);
        }
    }
    while(Path(source,target)){
        int flow = minResidual(source,target);
        Update(flow,source,target,result);
    }
    if(result == 0 && changed) return max_trains(B,A,false); // caso as estações source e target estejam trocadas, corre-se o codigo novamente, com as estações trocadas
    else return result;
}

