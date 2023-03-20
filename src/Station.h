//
// Created by Utilizador on 11/03/2023.
//

#ifndef STATION_H
#define STATION_H

#include "Graph.h"
#include <string>
using namespace std;

class Station : public Graph, public Vertex {
public:
    Station(string name);
    Station(string name, string district, string municipality, string township, string line);
    bool operator<(const Station& station2) const;

    const string getName() const;
    const string getDistrict() const;
    const string getMunicipality() const;
    const string getTownship() const;
    const string getLine() const;

    void setName(const string name);
    void setDistrict(const string district);
    void setMunicipality(const string municipality);
    void setTownship(const string township);
    void setLine(const string line);

private:
    string name_;
    string district_;
    string municipality_;
    string township_;
    string line_;
};

#endif //STATION_H
