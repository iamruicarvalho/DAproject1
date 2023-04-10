//
// Created by Utilizador on 12/03/2023.
//
#include <iostream>
#include <cstring>
#include "NetworkManager.h"

using namespace std;
/**
 * Constructor
 */
NetworkManager::NetworkManager() {
}

/**
 * Lê os ficheiros stations.csv e network.csv e cria um grafo com as estações (vertices) e ligações (edges).
 * Guardamos também as estações numa hash table para facilitar a procura de estações por id e nome.
 * O id da estação é feito por auto-incrementação.
 * Complexidade temporal: O(n+m), onde n é o número de estações e m é o número de ligações.
 * @return
 */
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

/**
 * Mostra as estações com os dados nome, distrito, concelho, freguesia e linha
 * Complexidade temporal: O(n), onde n é o número de estações
 */
void NetworkManager::listStations() {
    cout << "\n[NAME | DISTRICT | MUNICIPALITY | TOWNSHIP | LINE]";
    cout << "\n--------------------------------------------------\n";

    //int k = 1;
    for (auto station : stationsSet) {
        cout << station.getName() << " | " <<
             station.getDistrict() << " | " <<
             station.getMunicipality() << " | " <<
             station.getTownship() << " | " <<
             station.getLine() << endl;
    }
}

/**
 * Mostra as ligações com os dados estação A, estação B, capacidade e serviço
 * Complexidade temporal: O(m), onde m é o número de ligações
 */
void NetworkManager::listConnections() {
    cout << "\n[STATION_A | STATION_B | CAPACITY | SERVICE]";
    cout << "\n--------------------------------------------\n";
    for (auto connection : networkSet) {
        cout << connection.getStationA() << " | " <<
            connection.getStationB() << " | " <<
            connection.getCapacity() << " | " <<
            connection.getService() << endl;
    }
}

//2.1
/**
 * Verfica se o Vertex w foi visitado e se o residual é maior que 0 e se for, adiciona o w à queue q e marca-o como visitado
 * Complexidade temporal: O(1)
 * @param q Vertex queue, guarda as estações a visitar
 * @param e Edge, ligação a verificar
 * @param w Vertex, estação a verificar
 * @param residual double, residual a verificar
 */
void NetworkManager::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * Encontra o caminho aumentante e retorna true se existir
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param s Vertex, estação de origem
 * @param t Vertex, estação de destino
 * @return bool, true se existir caminho aumentante
 */
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

/**
 * Calcula o valor do residual mínimo
 * Complexidade temporal: O(n), onde n é o número de estações
 * @param s Vertex, estação de origem
 * @param t Vertex, estação de destino
 * @return double, valor do residual mínimo
 */
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
/**
 * Atualiza o fluxo das arestas do caminho aumentante
 * Complexidade temporal: O(n), onde n é o número de estações
 * @param s Vertex, estação de origem
 * @param t Vertex, estação de destino
 * @param f double, fluxo a atualizar
 */

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
/**
 * Calcula o número máximo de comboios que podem circular entre duas estações
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param A string, estação de origem
 * @param B string, estação de destino
 * @return double, número máximo de comboios que podem circular entre as duas estações
 */

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

/**
 * Calcula o número máximo de comboios que podem circular entre todas as estações
 * Complexidade temporal: O(n^3), onde n é o número de estações
 * @return pair<int,pair<string,string>>, par com o número máximo de comboios e as estações de origem e destino
 */
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
            if(comparing == result){
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
/**
 * Calcula o número de comboios por municipio
 * Complexidade temporal: O(n), onde n é o número de estações
 * @param k int, top k-th de municipios a mostrar
 */
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
    double max = vec[1].second;
    auto c = vec.begin();
    int i = 1;
    c++;
    while(k>0){
        if(c->second < max){
            max = c->second;
            k--;
            if(k==0)break;
            i++;
        }
        cout <<"Em "<<i<<"º lugar o municipio: "<< c->first << " com: " << c->second << " comboios." << endl;
        c++;
    }
}
/**
 * Calcula o número de comboios por distrito
 * Complexidade temporal: O(n), onde n é o número de estações
 * @param k int, top k-th de distritos a mostrar
 */
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
    double max = vec[1].second;
    auto c = vec.begin();
    int i = 1;
    c++;
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
/**
 * Calcula o número máximo de comboios que podem chegar a uma estação
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @return int, número máximo de comboios que podem chegar a uma estação
 * @param arrivingStation string, estação de destino
 */
int NetworkManager::maxTrainsArrivingAtStation(const std::string &arrivingStation) {
    int result = max_trains("superStation", arrivingStation);
    result /= 2;
    return result;
}


/**
 * Comparador para a priority queue
 * Complexidade temporal: O(1)
 */

//3.1
class NodeComparator {
public:
    bool operator()(Vertex *node1, const Vertex* node2) {
        return node1->getCost() > node2->getCost();
    }
};

/**
 * Calcula o caminho com melhor custo entre duas estações
 * Complexidade temporal: O(nmlogn), onde n é o número de estações e m é o número de ligações
 * @return vector<pair<string, int>>, caminho com melhor custo entre duas estações
 * @param first string, estação de origem
 * @param second string, estação de destino
 */
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
            std::cout << "Shortest path from " << first << " to " << second << " is:\n";
            for (auto node : currentVertex->getPathForCost()) {
                std::cout << " " << node.first<<endl;
                if (node.second < flow) {
                    flow = node.second;
                }
            }
            std::cout << " (cost without flow = " << currentVertex->getCost()<<")" << std::endl;
            std::cout << " (cost with flow = " << currentVertex->getCost() * flow  <<")" << std::endl;
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
/**
 * Coloca a ligação entre duas estações em modo bloqueado
 * Complexidade temporal: O(n), onde n é o número de estações
 * @param A string, estação de origem
 * @param B string, estação de destino
 * @return bool, true se a ligação foi bloqueada, false caso contrário
 */

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
/**
 * Coloca a ligação entre duas estações em modo desbloqueado
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param A string, estação de origem
 * @param B string, estação de destino
 * @return bool, true se a ligação foi desbloqueada, false caso contrário
 */
bool NetworkManager::remove_block(std::string A, std::string B) {
    int station_start = stations_code_reverse[A];
    int station_finish = stations_code_reverse[B];
    if(station_start == 0 || station_finish==0) return false;
    Vertex *first = findVertex(station_start);
    Vertex *second = findVertex(station_finish);
    for(auto it = edgesBlocked.begin();it!=edgesBlocked.end(); it++ ){
        pair<Edge*,Edge*> my_pair =*it;
        if((my_pair.first->getDest()==first && my_pair.first->getOrig()==second) || (my_pair.first->getDest()==second && my_pair.first->getOrig()==first)){
            my_pair.first->setSelected(false);
            my_pair.second->setSelected(false);
            edgesBlocked.erase(it);
            return true;
        }
    }
    return false;
}

//4.1
/**
 * Verfica se o Vertex w foi visitado e se o residual é maior que 0 e se for
 * Adiciona o Vertex w à queue q e marca-o como visitado
 * Esta função não considera as ligações bloqueadas
 * Complexidade temporal: O(1)
 * @param q Vertex queue, guarda as estações a visitar
 * @param e Edge, ligação a verificar
 * @param w Vertex, estação a verificar
 * @param residual double, residual a verificar
 */

void NetworkManager::testAndVisitWithBlocks(std::queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0 && !(e->isSelected())) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}
/**
 * Encontra um caminho aumentante a partir da estação s até à estação t tendo em conta as ligações bloqueadas
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param s Vertex, estação de origem
 * @param t Vertex, estação de destino
 * @return
 */
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
/**
 * Encontra o maximo de comboios que podem circular entre duas estações tendo em conta as ligações bloqueadas
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param A String, estação de origem
 * @param B string, estação de destino
 * @return int, número máximo de comboios que podem circular entre as duas estações
 */

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
/**
 * Comparador para ordenar as estações por ordem decrescente de capacidade e caso igual por ordem alfabética
 * @param x pair<string,int>, estação e capacidade
 * @param y pair<string,int>, estação e capacidade
 * @return bool, true se a capacidade de x é maior que y, false caso contrário
 */
static bool comp(pair<string, int>& x, pair<string, int>& y) {
    if (x.second == y.second) {
        return x.first < y.first;
    }
    return x.second > y.second;
}

/**
 * Coloca a flag de teste a true nas ligações que estão a ser testadas
 * Complexidade temporal: O(1)
 * @param that pair<Edge*,Edge*>, ligações que estão a ser testadas
 */
void NetworkManager::setEdgeTesting(pair<Edge*,Edge*> that) {
    that.first->setTesting(true);
    that.second->setTesting(true);
}
/**
 * Remove a flag de teste das ligações que estão a ser testadas
 * Complexidade temporal: O(1)
 * @param that pair<Edge*,Edge*>, ligações que estão a ser testadas
 */
void NetworkManager::removeEdgeTesting(pair<Edge *, Edge *> that) {
    that.first->setTesting(false);
    that.second->setTesting(false);
}
/**
 * Encontra as estações mais afetadas por um corte de uma linha
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param rank int, número de estações a mostrar
 */
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
        for(int i = 0; i<rank; i++){
            pair<string,int> to_cout = my_vector[i];
            if(to_cout.second==0){
                if(i==0){
                    cout << "Não há estações afetadas por este corte" << endl;
                }
                else {
                    cout << "Não há mais estações afetadas por este corte" << endl;
                }
                break;
            }
            cout << i+1 <<"ª estação mais afetada: " << to_cout.first << "    " << capacityNormal[to_cout.first] << " -> " << capacityNormal[to_cout.first] - capacityCutted[to_cout.first] << " ." << endl;
        }
        removeEdgeTesting(edges);
        cout << endl;
    }
}
/**
 * Encontra o caminho mais curto em numero de comboios entre duas estações
 * Complexidade temporal: O(nm), onde n é o número de estações e m é o número de ligações
 * @param source string, estação de origem
 * @param target string, estação de destino
 */
void NetworkManager:: bfs(string source, string target){
    for(auto vertex: vertexSet){
        vertex->setVisited(false);
        vertex->setPath(nullptr);
        vertex->setDist(0);
    }
    Vertex* start = findVertex(stations_code_reverse[source]);
    Vertex* end = findVertex(stations_code_reverse[target]);
    start->setVisited(true);
    queue<Vertex*> q;
    q.push(start);
    while(!q.empty()){
        Vertex* v = q.front();
        q.pop();
        for(auto edge: v->getAdj()){
            if(!edge->getDest()->isVisited() && edge->getDest()->getDist() - v->getDist()+1 > 0){
                edge->getDest()->setVisited(true);
                edge->getDest()->setPath(edge);
                edge->getDest()->setDist(v->getDist()+1);
                q.push(edge->getDest());
            }
        }
    }
    if(end->isVisited()){
        cout<< "Existe caminho entre " << source << " e " << target << endl;
        cout << "O caminho é: " << endl;
        Vertex* v = end;
        while(v->getPath()!= nullptr){
            cout << stations_code[v->getId()] << " -> ";
            v = v->getPath()->getOrig();
        }
        cout << stations_code[v->getId()] << endl;
        cout << "O comprimento do caminho é: " << end->getDist() << endl;
    }
}

