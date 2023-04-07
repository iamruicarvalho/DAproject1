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
        int cost;
        if(service=="ALFA PENDULAR"){
            cost = 4;
        }
        if(service=="STANDARD") {
            cost = 2;
        }
        int code_StationA = stations_code_reverse[stationA];
        int code_StationB = stations_code_reverse[stationB];

        addEdge(code_StationA, code_StationB, stod(capacity)/2, service, cost);
        addEdge(code_StationB, code_StationA, stod(capacity)/2, service, cost);
    }
    networkFile.close();
    cout << "In all, there are " << networkSet.size() << " possible connections in the provided railway network!"
         << endl;
    Station superStation("superStation");
    stations_code_reverse[superStation.getName()] = stationsSet.size()+1;    // id big enough to be unique
    stations_code[stationsSet.size()+1] = superStation.getName();

    int superStationID = stations_code_reverse[superStation.getName()];
    addVertex(superStationID, "none", "none", "none");
    Vertex* superSource = findVertex(superStationID);

    for (Vertex* v : vertexSet) {
        if (v->getAdj().size() == 1) {
            superSource->addEdge(v, INF, "", v->getCost());
        }
    }
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



//2.1

void NetworkManager::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0 && !(e->isTesting())) {
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

double NetworkManager::max_trains(string A, string B) {
    double result_final=0;
    int source = stations_code_reverse[A];
    int target = stations_code_reverse[B];
    if(source == 0 | target==0) return -1;

    for (auto vertex: vertexSet) {
        for (auto edge: vertex->getAdj()) {
            edge->setFlow(0);
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

struct PairHash {
    size_t operator()(const pair<string, string> &p) const {
        return hash<string>()(p.first) ^ hash<string>()(p.second);
    }
};

vector<pair<int,pair<string,string>>> NetworkManager::max_of_max_trains() {
    vector<pair<int,pair<string,string>>> that;
    unordered_set<pair<string,string>,PairHash> edges_verified{};
    int result = 0;
    int comparing;
    pair<int, pair<string,string>> all;
    for(auto vertex: vertexSet){
        for(auto edge: vertex->getAdj()){
            pair<string,string> connection1 = make_pair(stations_code[edge->getDest()->getId()],stations_code[vertex->getId()]);
            pair<string,string> connection2 = make_pair(stations_code[vertex->getId()],stations_code[edge->getDest()->getId()]);
            if(connection1.first == "superStation" || connection1.first == "superStation") continue;
            if(edges_verified.count(connection1) || edges_verified.count(connection2)) continue;
            edges_verified.insert(connection1);
            string A = connection1.second;
            string B = connection1.first;
            comparing = max_trains(A,B);
            if(comparing==result){
                all.first = result;
                all.second.first = A;
                all.second.second = B;
                that.push_back(all);
                continue;
            }
            result = max(comparing,result);
            // cout << "comparing: " << comparing << " result: " <<result << endl;
            if (result == comparing) {
                all.first = result;
                all.second.first = A;
                all.second.second = B;
                that.clear();
                that.push_back(all);
            }
        }
    }
    return that;
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
        if(c->second < max){
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
        if(c->second < max){
            k--;
            if(k==0)break;
            i++;
        }
        cout <<"Em "<<i<<"º lugar o distrito: "<< c->first << " com: " << c->second << " comboios." << endl;
        c++;
    }
}



//2.4

int NetworkManager::maxTrainsArrivingAtStation(const std::string &arrivingStation) {
    int result = max_trains("superStation", arrivingStation);
    result /= 2;
    return result;
}




//3.1
class NodeComparator {
public:
    bool operator()(Vertex *node1, const Vertex* node2) {
        return node1->getCost() > node2->getCost();
    }
};


// function to perform Dijkstra's algorithm
void NetworkManager::dijkstra(string first, string second) {
    std::priority_queue<Vertex*, std::vector<Vertex*>, NodeComparator> pq;
    int source = stations_code_reverse[first];
    double flow = numeric_limits<int>::max();
    Vertex* startNode = findVertex(source);
    startNode->setCost(0.0);
    startNode->addPathForCost({first, numeric_limits<int>::max()});
    pq.push(startNode);
    while (!pq.empty()) {
        Vertex* currentVertex = pq.top();
        pq.pop();
        if (currentVertex->isVisited()) {
            continue;
        }
        currentVertex->setVisited(true);
        if(currentVertex->getId() == stations_code_reverse[second]) {
            std::cout << "Shortest path from " << first << " to " << second << " is:";
            for (auto node : currentVertex->getPathForCost()) {
                std::cout << " " << node.first<<" com flow: "<<node.second<<endl;
                if (node.second < flow) {
                    flow = node.second;
                }
            }
            std::cout << " (cost = " << currentVertex->getCost() * flow  <<")" << std::endl;
            return;
        }
        for (auto edge : currentVertex->getAdj()) {
            Vertex* nextNode = edge->getDest();
            if (!nextNode->isVisited()) {
                double newCost = currentVertex->getCost() + edge->getCost();
                if (newCost < nextNode->getCost()) {
                    // found a shorter path to nextNode, update its cost and path
                    nextNode->setCost(newCost);
                    nextNode->setPathForCost(currentVertex->getPathForCost());
                    nextNode->addPathForCost({stations_code[nextNode->getId()], edge->getWeight()});
                    pq.push(nextNode);
                }
            }
        }
    }
}


// pré 4

bool NetworkManager::set_block(std::string A, std::string B) {
    int station_start = stations_code_reverse[A];
    int station_finish = stations_code_reverse[B];
    if(station_start == 0 || station_finish==0) return false;
    Vertex* first = findVertex(station_start);
    for(auto e1 : first->getAdj()){
        Vertex* x = e1->getDest();
        if (x->getId()== station_finish){
            if(e1->isSelected()) return false; // retorna falso por já ter sido estabelecido neste edge um bloqueio
            e1->setSelected(true);// quando este valor está a true, depois, ao fazer o augmenting path,verifica-se se isto está a true, e, se estiver, descarta-se
            for(auto e2: x->getAdj()){
                if (e2->getDest()->getId() == station_start ){
                    if(e2->isSelected()){
                        e1->setSelected(false);
                        return false;
                    }
                    e2->setSelected(true);
                    edgesBlocked.push_back(make_pair(e1,e2));
                    return true;
                }
            }
        }
    }
    return false;
}

bool NetworkManager::remove_block(std::string A, std::string B) {
    int station_start = stations_code_reverse[A];
    int station_finish = stations_code_reverse[B];
    if(station_start == 0 || station_finish==0) return false;
    Vertex *first = findVertex(station_start);
    pair<Edge*,Edge*> to_remove;
    for (auto e1: first->getAdj()) {
        Vertex *x = e1->getDest();
        if (x->getId() == station_finish) {
            if(!(e1->isSelected())) return false; // a mesma coisa da função de cima, só que ao contrário
            e1->setSelected(false);
            for (auto e2: x->getAdj()) {
                if(!(e2->isSelected())){
                    e1->setSelected(true);
                    return false;
                }
                if (e2->getDest()->getId() == station_start) {
                    e2->setSelected(false);
                    to_remove = make_pair(e1,e2);
                    break;
                }
            }
            for (auto it = edgesBlocked.begin();it!=edgesBlocked.end();it++){
                if (it->first == to_remove.first && it->second == to_remove.second){
                    edgesBlocked.erase(it);
                    return true;
                }
            }
        }
    }
    return false;
}

//4.1

void NetworkManager::testAndVisitWithBlocks(std::queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0 && !(e->isSelected())) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool NetworkManager::augmentingPathWithBlocks(Vertex *s, Vertex *t) {
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
            testAndVisitWithBlocks(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisitWithBlocks(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

int NetworkManager::max_trains_with_blocks (string A, string B) {
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
    while (augmentingPathWithBlocks(start,end)) {
        double flow = minResidual(start,end);
        update(start,end,flow);
        result_final+=flow;
    }
    return result_final*2;
}

//4.2
/*
void NetworkManager::testAndVisitWithSpecificBlock(std::queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0 && !(e->isTesting())) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool NetworkManager::augmentingPathWithSpecificBlock(Vertex *s, Vertex *t) {
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
            testAndVisitWithSpecificBlock(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisitWithSpecificBlock(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

int NetworkManager::max_trains_with_specific_block (string A, string B) {
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
    Vertex* start = findVertex(source);
    Vertex* end = findVertex(target);
    while (augmentingPathWithSpecificBlock(start,end)) {
        double flow = minResidual(start,end);
        update(start,end,flow);
        result_final+=flow;
    }
    return result_final*2;
}
*/

static bool comp(pair<string, int>& x, pair<string, int>& y) {
    if (x.second == y.second) {
        return x.first < y.first;
    }
    return x.second > y.second;
}

void NetworkManager::add_or_update(std::string key, int value) {
    // Verifica se a chave já existe no map
    if (my_map.find(key) == my_map.end()) {
        // A chave não existe, então insere um novo par chave-valor
        my_map[key] = value;
    } else {
        // A chave já existe, então atualiza o valor existente
        my_map[key] += value;
    }
}


void NetworkManager::setEdgeTesting(pair<Edge*,Edge*> that) {
    that.first->setTesting(true);
    that.second->setTesting(true);
}

void NetworkManager::removeEdgeTesting(pair<Edge *, Edge *> that) {
    that.first->setTesting(false);
    that.second->setTesting(false);
}

void NetworkManager::most_affected_stations(int rank) {
    unordered_map<string,int> capacityNormal;
    unordered_map<string,int> capacityCutted;
    for(auto station: stationsSet){
        int x = maxTrainsArrivingAtStation(station.getName());
        capacityNormal[station.getName()] = x;
    }
    for(auto edges:edgesBlocked) {
        setEdgeTesting(edges);
        cout << "Por causa do corte da linha entre " << stations_code[edges.first->getOrig()->getId()] << " e " << stations_code[edges.first->getDest()->getId()] <<", as estações mais afetadas foram as seguintes:" << endl;
        for(auto station:stationsSet){
            int y = maxTrainsArrivingAtStation(station.getName());
            capacityCutted[station.getName()] = capacityNormal[station.getName()] - y;
        }
        vector<pair<string, int>> my_vector(capacityCutted.begin(), capacityCutted.end());
        sort(my_vector.begin(),my_vector.end(),comp);
        for(int i = 0; i<rank;i++){
            pair<string,int> to_cout = my_vector[i];
            if(to_cout.second==0){
                cout << "Não há mais estações afetadas por este corte" << endl;
                break;
            }
            cout << i+1 <<"ª estação mais afetada: " << to_cout.first << "    " << capacityNormal[to_cout.first] << " -> " << capacityNormal[to_cout.first] - capacityCutted[to_cout.first] << " ." << endl;
        }
        removeEdgeTesting(edges);
        cout << endl;
    }
}

