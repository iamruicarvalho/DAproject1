// By: Gonçalo Leão

#include "Graph.h"
/**
 * Retorna o numero de vertices do grafo
 * Complexidade: O(1)
 * @return int, numero de vertices do grafo
 */
int Graph::getNumVertex() const {
    return vertexSet.size();
}
/**
 * Retorna os vertices do grafo
 * Complexidade: O(1)
 * @return vector<Vertex*>, vertices do grafo
 */
std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * Retorna o Vertex com o id passado por parametro
 * Complexidade: O(n)
 * @param id int, id do vertice a procurar
 * @return Vertex*, vertice com o id passado por parametro
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/**
 * Retorna o indice do vertice com o id passado por parametro
 * Complexidade: O(n)
 * @param id const int&, id do vertice a procurar
 * @return int, indice do vertice com o id passado por parametro
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
/**
 * Adiciona um vertice ao grafo
 * Complexidade: O(n)
 * @param id const int&, id do vertice a adicionar
 * @param district string, distrito do vertice a adicionar
 * @param municipality string, município do vertice a adicionar
 * @param township string, cidade do vertice a adicionar
 * @return bool, true se o vertice foi adicionado com sucesso, false caso contrario
 */
bool Graph::addVertex(const int &id, string district, string municipality, string township) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, district, municipality, township));
    return true;
}

/**
 * Adiciona uma aresta ao grafo
 * Complexidade: O(n)
 * @param sourc const int&, id do vertice de origem
 * @param dest const int&, id do vertice de destino
 * @param w double, peso da aresta
 * @param service string, serviço da aresta
 * @param cost int, custo da aresta
 * @return bool, true se a aresta foi adicionada com sucesso, false caso contrario
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w, string service, int cost) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service, cost);
    return true;
}
/**
 * Adiciona uma aresta bidirecional ao grafo
 * Complexidade: O(n)
 * @param sourc const int&, id do vertice de origem
 * @param dest const int&, id do vertice de destino
 * @param w double, peso da aresta
 * @param service string, serviço da aresta
 * @param cost int, custo da aresta
 * @return bool, true se a aresta foi adicionada com sucesso, false caso contrario
 */
bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w, string service, int cost) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service,cost);
    auto e2 = v2->addEdge(v1, w, service, cost);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}
/**
 * Apaga a matriz passada por parametro
 * Complexidade: O(n^2)
 * @param m int**, matriz a apagar
 * @param n int, tamanho da matriz
 */
void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}
/**
 * Apaga a matriz de distancias e a matriz de caminhos
 * Complexidade: O(n^2)
 * @param m double**, matriz a apagar
 * @param n int, tamanho da matriz
 */
void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}
/**
 * Construtor da classe Graph
 * Complexidade: O(n^2)
 */
Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}