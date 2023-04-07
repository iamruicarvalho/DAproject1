// By: Gonçalo Leão

#include "VertexEdge.h"

/************************* Vertex  **************************/
/**
 * Construtor de um vértice com um dado id.
 * Complexidade: O(1)
 * @param id int, id do vértice
 */
Vertex::Vertex(int id): id(id) {}
/**
 * Construtor de um vértice com um dado id, distrito, município e cidade.
 * Complexidade: O(1)
 * @param id int, id do vértice
 * @param district string, distrito do vértice
 * @param municipality string, município do vértice
 * @param township string, cidade do vértice
 */
Vertex::Vertex(int id, string district, string municipality, string township): id(id), district_(district), municipality_(municipality), township_(township) {}
/**
 * Construtor de um vértice com um dado id, distrito, município, cidade e linha.
 * Complexidade: O(1)
 * @param id int, id do vértice
 * @param district string, distrito do vértice
 * @param municipality string, município do vértice
 * @param township string, cidade do vértice
 * @param line string, linha do vértice
 */
Vertex::Vertex() {

}

/**
 * Retorna o id do vértice
 * Complexidade: O(1)
 * @param d Vertex*, vértice de destino
 * @param w double, peso da aresta
 * @param service string, serviço do vértice
 * @param cost int, custo do vértice
 * @return Edge*, aresta criada
 */

Edge * Vertex::addEdge(Vertex *d, double w, string service, int cost) {
    auto newEdge = new Edge(this, d, w, service, cost);
    adj.push_back(newEdge);
    d->capacity+=w;
    newEdge->setReverse(new Edge(d,this,w,service,cost));
    d->incoming.push_back(newEdge);
    return newEdge;
}

/**
 * Remove uma aresta do vértice
 * Complexidade: O(n)
 * @param destID int, id do vértice de destino
 * @return bool, true se a aresta foi removida, false caso contrário
 */
bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}
/**
 * Operador de comparação de vértices
 * Complexidade: O(1)
 * @param vertex Vertex&, vértice a comparar
 * @return bool, true se a distância do vértice for menor, false caso contrário
 */
bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

/**
 * Retorna o id do vértice
 * Complexidade: O(1)
 * @return int, id do vértice
 */
int Vertex::getId() const {
    return this->id;
}
/**
 * Retorna o vetor de arestas do vértice
 * Complexidade: O(1)
 * @return vector<Edge*>, vetor de arestas do vértice
 */
std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}
/**
 * Retorna o valor de visited do vértice
 * Complexidade: O(1)
 * @return bool, se o vertice foi visitado retorna true, false caso contrário
 */
bool Vertex::isVisited() const {
    return this->visited;
}
/**
 * Verifica se o vértice está a ser processado
 * Complexidade: O(1)
 * @return bool, se o vertice está a ser processado retorna true, false caso contrário
 */
bool Vertex::isProcessing() const {
    return this->processing;
}
/**
 * Retorna o valor de indegree do vértice
 * Complexidade: O(1)
 * @return unsigned int, valor de indegree do vértice
 */
unsigned int Vertex::getIndegree() const {
    return this->indegree;
}
/**
 * Retorna a distância do vértice
 * Complexidade: O(1)
 * @return double, distância do vértice
 */
double Vertex::getDist() const {
    return this->dist;
}
/**
 * Retorna o caminho para o vértice
 * Complexidade: O(1)
 * @return Edge*, caminho para o vértice
 */
Edge *Vertex::getPath() const {
    return this->path;
}
/**
 * Retorna o vetor de arestas de entrada do vértice
 * Complexidade: O(1)
 * @return vector<Edge*>, vetor de arestas de entrada do vértice
 */
std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}
/**
 * Verifica se o vértice está bloqueado
 * Complexidade: O(1)
 * @return bool, se o vértice está bloqueado retorna true, false caso contrário
 */
bool Vertex::isBlocked() {
    return blocked;
}
/**
 * Define o id do vértice
 * Complexidade: O(1)
 * @param id int, id do vértice
 */
void Vertex::setId(int id) {
    this->id = id;
}
/**
 * Define se o vértice foi visitado
 * Complexidade: O(1)
 * @param visited bool, se já foi visitado ou não
 */
void Vertex::setVisited(bool visited) {
    this->visited = visited;
}
/**
 * Define se o vértice está a ser processado
 * Complexidade: O(1)
 * @param processing bool, se está a ser processado ou não
 */
void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}
/**
 * Define o valor de indegree do vértice
 * Complexidade: O(1)
 * @param indegree unsigned int, valor de indegree do vértice
 */
void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}
/**
 * Define a distância do vértice
 * Complexidade: O(1)
 * @param dist double, distância do vértice
 */
void Vertex::setDist(double dist) {
    this->dist = dist;
}
/**
 * Define o caminho para o vértice
 * Complexidade: O(1)
 * @param path Edge*, caminho para o vértice
 */
void Vertex::setPath(Edge *path) {
    this->path = path;
}
/**
 * Retorna o distrito do vértice
 * Complexidade: O(1)
 * @return const string, distrito do vértice
 */
const string Vertex::getDistrict() const {
    return district_;
}
/**
 * Retorna o concelho do vértice
 * Complexidade: O(1)
 * @return const string, concelho do vértice
 */
const string Vertex::getMunicipality() const {
    return municipality_;
}
/**
 * Retorna a cidade do vértice
 * Complexidade: O(1)
 * @return const string, cidade do vértice
 */
const string Vertex::getTownship() const {
    return township_;
}
/**
 * Define a estação como bloqueada
 * Complexidade: O(1)
 */
void Vertex::setBlock() {
    this->blocked = true;
}
/**
 * Retorna a capacidade da estação
 * Complexidade: O(1)
 * @return double, capacidade da estaçãor
 */
double const Vertex::getCapacity() {
    return this->capacity;
}

/********************** Edge  ****************************/
/**
 * Construtor de uma aresta tendo como parâmetros o vértice de origem, o vértice de destino, o peso da aresta, o serviço prestado e o custo do serviço
 * @param orig Vertex*, vértice de origem
 * @param dest Vertex*, vértice de destino
 * @param w double, peso da aresta
 * @param service string, serviço prestado
 * @param cost int, custo do serviço
 */
Edge::Edge(Vertex *orig, Vertex *dest, double w, string service, int cost): orig(orig), dest(dest), weight(w), service(service), cost(cost) {}
/**
 * Construtor de uma aresta default
 * Complexidade: O(1)
 */
Edge::Edge(){

}
/**
 * Retorna o vértice de destino da aresta
 * Complexidade: O(1)
 * @return Vertex*, vértice de destino da aresta
 */
Vertex * Edge::getDest() const {
    return this->dest;
}
/**
 * Retorna o peso da aresta
 * Complexidade: O(1)
 * @return double, peso da aresta
 */
double Edge::getWeight() const {
    return this->weight;
}
/**
 * Retorna o vértice de origem da aresta
 * Complexidade: O(1)
 * @return Vertex*, vértice de origem da aresta
 */
Vertex * Edge::getOrig() const {
    return this->orig;
}
/**
 * Retorna o reverso da aresta
 * Complexidade: O(1)
 * @return Edge*, reverso da aresta
 */
Edge *Edge::getReverse() const {
    return this->reverse;
}
/**
 * Retorna se é selecionada a aresta ou não
 * @return bool, se é selecionada a aresta ou não
 */
bool Edge::isSelected() const {
    return this->selected;
}
/**
 * Retorna se a aresta está a ser testada ou não
 * Complexidade: O(1)
 * @return bool, se a aresta está a ser testada ou não
 */
bool Edge::isTesting() const {
    return this->testing;
}
/**
 * Retorna o fluxo da aresta
 * Complexidade: O(1)
 * @return double, fluxo da aresta
 */
double Edge::getFlow() const {
    return flow;
}
/**
 * Define se a aresta está selecionada ou não
 * Complexidade: O(1)
 * @param selected bool, se a aresta está selecionada ou não
 */
void Edge::setSelected(bool selected) {
    this->selected = selected;
}
/**
 * Define se a aresta está a ser testada ou não
 * Complexidade: O(1)
 * @param testing bool, se a aresta está a ser testada ou não
 */
void Edge::setTesting(bool testing) {
    this->testing = testing;
}
/**
 * Define o reverso da aresta
 * Complexidade: O(1)
 * @param reverse Edge*, reverso da aresta
 */
void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}
/**
 * Define o fluxo da aresta
 * Complexidade: O(1)
 * @param flow double, fluxo da aresta
 */
void Edge::setFlow(double flow) {
    this->flow = flow;
}
/**
 * Define o serviço prestado
 * Complexidade: O(1)
 * @param service string, serviço prestado
 */
void Edge::setService(std::string service) {
    this->service = service;
}
/**
 * Retorna o serviço prestado
 * Complexidade: O(1)
 * @return string, serviço prestado
 */
std::string Edge::getService() {
    return this->service;
}
/**
 * Define o vértice anterior
 * Complexidade: O(1)
 * @param prev int, vértice anterior
 */
void Vertex::setPrev(int prev) {
    this->prev = prev;
}
/**
 * Retorna o vértice anterior
 * Complexidade: O(1)
 * @return int, vértice anterior
 */
int Vertex::getPrev() const{
    return this->prev;
}
/**
 * Retorna o custo até ao vértice
 * Complexidade: O(1)
 * @return int, custo até ao vértice
 */
int Vertex::getCost() const{
    return this->cost;
}
/**
 * Define o custo até ao vértice
 * Complexidade: O(1)
 * @param cost int, custo até ao vértice
 */
void Vertex::setCost(int cost) {
    this->cost = cost;
}
/**
 * Retorna o custo da aresta
 * Complexidade: O(1)
 * @return int, custo da aresta
 */
int Edge::getCost() {
    return this->cost;
}
/**
 * Define o custo da aresta
 * Complexidade: O(1)
 * @param cost int, custo da aresta
 */
void Edge::setCost(int cost) {
    this->cost = cost;
}

/**
 * Adiciona o nome da estação e o flow para lá chegar ao caminho por custo
 * Complexidade: O(1)
 * @param caminho pair<string, int>, nome da estação e o flow para lá chegar
 */
void Vertex::addPathForCost(pair<string, int> caminho) {
    this->pathForCost.push_back(caminho);
}
/**
 * Retorna o caminho por custo
 * Complexidade: O(1)
 * @return vector<pair<string, int>>, caminho por custo
 */
vector<pair<string,int>> Vertex::getPathForCost() const{
    return this->pathForCost;
}
/**
 * Define o caminho por custo
 * Complexidade: O(1)
 * @param pathForCost vector<pair<string, int>>, caminho por custo
 */
void Vertex::setPathForCost(std::vector<pair<string,int>> pathForCost) {
    this->pathForCost = pathForCost;}