//
// Created by Utilizador on 12/03/2023.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "NetworkManager.h"

using namespace std;

NetworkManager::NetworkManager() {
}

void NetworkManager::readFiles() {
    cout << "Loading files..." << endl;

    // read stations.csv
    int station_count = 0;
    std::ifstream stationsFile;
    stationsFile.open("../resources/stations.csv");
    if (!stationsFile.is_open()) {
        cout << "File not found\n";
        return;
    }
    string name, district, municipality, township, line;
    int i = 0;
    while (getline(stationsFile, line)) {
        istringstream iss(line);
        getline(iss, name, ',');
        if(name.front()=='\"'){
            string temp;
            getline(iss, temp, ',');
            name+= "." + temp;
        }
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        getline(iss, line, '\0');

        Station station(name, district, municipality, township, line);
        stationsSet.insert(station);

        if (!(stations_code_reverse.count(name)) && name != "NAME") {
            i++;
            stations_code_reverse[name] = i;
            stations_code[i] = name;
            addVertex(i,district,municipality,township);
        }
    }
    stationsFile.close();
    cout << "There are " << stationsSet.size() << " stations!" << endl;


    // read network.csv
    int network_count = 0;
    std::ifstream networkFile;
    networkFile.open("../resources/network.csv");
    if (!networkFile.is_open()) {
        cout << "File not found\n";
        return;
    }

    getline(networkFile, line);
    while (getline(networkFile, line)) {
        //row.clear();
        string stationA, stationB, capacity, service;
        istringstream iss(line);
        getline(iss, stationA, ',');
        getline(iss, stationB, ',');
        getline(iss, capacity, ',');
        getline(iss, service, '\0');

        Network network(stationA, stationB, stoi(capacity), service);
        networkSet.insert(network);

        int code_StationA = stations_code_reverse[stationA];
        int code_StationB = stations_code_reverse[stationB];
        addEdge(code_StationA, code_StationB, stod(capacity)/2);
        addEdge(code_StationB, code_StationA, stod(capacity)/2);
    }
    networkFile.close();
    cout << "In all, there are " << networkSet.size() << " possible connections in the provided railway network!"
         << endl;
}


//Bloquear as linhas atraves da string
//retorna um set com os ids de cada station que fica cortada por causa da linha que usa
set<int> NetworkManager::returnBlockedStations(const string &blockLine) {
    set<int> result;
    for (auto &c: stationsSet) {
        if (c.getLine() == blockLine) {
            result.insert(stations_code_reverse[c.getName()]);
        }
    }
    return result;
}

void NetworkManager::setBlockLine(const string &blockline) {
    set<int> blockeds = returnBlockedStations(blockline);
    for (auto &c: blockeds) {
        for (auto d: vertexSet) {
            if (c == d->getId()) {
                d->setBlock();
            }
        }
    }
}

//2.1

void NetworkManager::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool NetworkManager::augmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double NetworkManager::minResidual(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void NetworkManager::update(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

int NetworkManager::max_trains(string A, string B) {
    int result_final=0;
    int source = stations_code_reverse[A];
    int target = stations_code_reverse[B];
    if(source == 0 | target==0) return -1;
    for (auto vertex: vertexSet) {
        for (auto edge: vertex->getAdj()) {
            edge->setFlow(0);
            edge->setReverse(nullptr);
        }
    }
    Vertex* start= findVertex(source);
    Vertex* end = findVertex(target);
    while (augmentingPath(start,end)) {
        double flow = minResidual(start,end);
        update(start,end,flow);
        result_final+=flow;
    }
    return result_final*2;
}

//2.2

pair<int,pair<string,string>> NetworkManager::max_of_max_trains() {
    int result=0;
    int comparing;
    pair<int,pair<string,string>> all;
    for(int i=1;i<stationsSet.size()-1;i++){
        for(int j=i+1;j<stationsSet.size();j++){
            string A = stations_code[i];
            string B = stations_code[j];
            comparing = max_trains(A,B);
            result = max(comparing,result);
            cout << "comparing: " << comparing << " result: " <<result << endl;
            if (result == comparing) {
                all.first = result;
                all.second.first = A;
                all.second.second = B;
            }
        }
    }
    return all;
}



//2.3
void NetworkManager::trainManagementByTownship(int k){
    unordered_map<string, double> result;
    for(auto c: vertexSet){
        result[c->getTownship()] += c->getCapacity();
    }

    vector<pair<string, double>> vec(result.begin(), result.end());

    // Sort the vector by the second element (the value) in descending order
    sort(vec.begin(), vec.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });
    double max = vec[0].second;
    auto c = vec.begin();
    int i = 1;
    while(k>0){
        if(c->second<max){
            k--;
            if(k==0)break;
            i++;
        }
        cout <<"Em "<<i<<"º lugar o concelho: "<< c->first << " com: " << c->second << " comboios." << endl;
        c++;
    }
}

void NetworkManager::trainManagementByMunicipality(int k){
    unordered_map<string, double> result;
    for(auto c: vertexSet){
        result[c->getMunicipality()] += c->getCapacity();
    }

    vector<pair<string, double>> vec(result.begin(), result.end());

    // Sort the vector by the second element (the value) in descending order
    sort(vec.begin(), vec.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });
    double max = vec[0].second;
    auto c = vec.begin();
    int i = 1;
    while(k>0){
        if(c->second<max){
            k--;
            if(k==0)break;
            i++;
        }
        cout <<"Em "<<i<<"º lugar o municipio: "<< c->first << " com: " << c->second << " comboios." << endl;
        c++;
    }
}

void NetworkManager::trainManagementByDistrict(int k){
    unordered_map<string, double> result;
    for(auto c: vertexSet){
        result[c->getDistrict()] += c->getCapacity();
    }

    vector<pair<string, double>> vec(result.begin(), result.end());

    // Sort the vector by the second element (the value) in descending order
    sort(vec.begin(), vec.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });
    double max = vec[0].second;
    auto c = vec.begin();
    int i = 1;
    while(k>0){
        if(c->second<max){
            k--;
            if(k==0)break;
            i++;
        }
        cout <<"Em "<<i<<"º lugar o distrito: "<< c->first << " com: " << c->second << " comboios." << endl;
        c++;
    }
}




//maximo de comboios entre 2 estações, com varias linhas bloqueada

void NetworkManager::max_of_max_trains_with_block(string blockLine) {
    setBlockStation(blockLine);
    int result = 0;
    int comparing;
    for(int i = 1; i < stationsSet.size() - 1; i++) {
        for(int j = i + 1; j < stationsSet.size(); j++) {
            string A = stations_code[i];
            string B = stations_code[j];
            comparing = max_trains(A, B);
            result = max(comparing, result);
            cout << "comparing: " << comparing << "; result: " << result << ";" << endl;
        }
    }
}


// 4.1

bool NetworkManager::set_block(std::string A, std::string B) {
    int station_start = stations_code_reverse[A];
    Vertex* first = findVertex(station_start);
    for(auto e : first->getAdj()){
        Vertex* x = e->getDest();
        if (x->getId()== stations_code_reverse[B]){
            e->setSelected(true);// quando este valor está a true, depois, ao fazer o augmenting path,verifica-se se isto está a true, e, se estiver, descarta-se
            return true;
        }
    }
    return false;
}

bool NetworkManager::remove_block(std::string A, std::string B) {
    int station_start = stations_code_reverse[A];
    Vertex* first = findVertex(station_start);
    for(auto e : first->getAdj()){
        Vertex* x = e->getDest();
        if (x->getId()== stations_code_reverse[B]){
            e->setSelected(false);
            return true;
        }
    }
    return false;
}


