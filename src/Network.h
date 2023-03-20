//
// Created by Bernardo Pinto on 06/03/2023.
//

#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Graph.h"
using namespace std;

class Network : public Graph {
public:
    Network(string stationA, string stationB);
    Network(string stationA, string stationB, int capacity, string service);

    const string getStationA() const;
    const string getStationB() const;
    const string getCapacity() const;
    const string getService() const;

    void setStationA(const string stationA);
    void setStationB(const string stationB);
    void setCapacity(const int capacity);
    void setService(const string service);

private:
    string stationA_;
    string stationB_;
    int capacity_;
    string service_;
};

#endif //NETWORK_H
