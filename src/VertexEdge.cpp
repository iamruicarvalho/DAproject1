// By: Gonçalo Leão

#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id): id(id) {}
Vertex::Vertex(int id, string district, string municipality, string township): id(id), district_(district), municipality_(municipality), township_(township) {}
Vertex::Vertex() {

}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge * Vertex::addEdge(Vertex *d, double w, string service, int cost) {
    auto newEdge = new Edge(this, d, w, service, cost);
    adj.push_back(newEdge);
    d->capacity+=w;
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
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

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}


int Vertex::getId() const {
    return this->id;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

bool Vertex::isBlocked() {
    return blocked;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}
const string Vertex::getDistrict() const {
    return district_;
}
const string Vertex::getMunicipality() const {
    return municipality_;
}
const string Vertex::getTownship() const {
    return township_;
}

void Vertex::setBlock() {
    this->blocked = true;
}
double const Vertex::getCapacity() {
    return this->capacity;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w, string service, int cost): orig(orig), dest(dest), weight(w), service(service), cost(cost) {}
Edge::Edge(){

}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}
void Edge::setService(std::string service) {
    this->service = service;
}
std::string Edge::getService() {
    return this->service;
}
void Vertex::setPrev(int prev) {
    this->prev = prev;
}
int Vertex::getPrev() const{
    return this->prev;
}
int Vertex::getCost() const{
    return this->cost;
}
void Vertex::setCost(int cost) {
    this->cost = cost;
}
int Edge::getCost() {
    return this->cost;
}
void Edge::setCost(int cost) {
    this->cost = cost;
}

void Vertex::addPathForCost(pair<string, int> caminho) {
    this->pathForCost.push_back(caminho);
}
vector<pair<string,int>> Vertex::getPathForCost() const{
    return this->pathForCost;
}
void Vertex::setPathForCost(std::vector<pair<string,int>> pathForCost) {
    this->pathForCost = pathForCost;}