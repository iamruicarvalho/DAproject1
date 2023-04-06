// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

class Edge;
using namespace std;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex();
    Vertex(int id);
    Vertex(int id, string district, string municipality, string township);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    bool isBlocked();
    double const getCapacity();

    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    void setBlock();
    Edge * addEdge(Vertex *dest, double w, string service, int cost);
    bool removeEdge(int destID);
    const string getDistrict() const;
    const string getMunicipality() const;
    const string getTownship() const;
    void setPrev(int prev);
    int getPrev() const;
    void setCost(int cost);
    int getCost() const;
    void addPathForCost(pair<string,int> caminho);
    vector<pair<string,int>> getPathForCost() const;
    void setPathForCost(vector<pair<string,int>> pathForCost);
    friend class MutablePriorityQueue<Vertex>;
protected:
    int id;                // identifier
    string district_;
    string municipality_;
    string township_;
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    bool blocked = false;

    double capacity = 0;
    vector<pair<string,int>> pathForCost;
    int prev;
    int cost = std::numeric_limits<double>::infinity();
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge();
    Edge(Vertex *orig, Vertex *dest, double w, string service, int cost);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    bool isTesting() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setTesting(bool testing);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    string getService() const;
    void setService(string service);
    string getService();
    void setCost(int cost);
    int getCost();

protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;
    bool testing = false; //para o 4.2


    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems

    string service;// for cost-related problems

    int cost = std::numeric_limits<double>::infinity();


};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */