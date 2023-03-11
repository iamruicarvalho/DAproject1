//
// Created by Utilizador on 11/03/2023.
//

#ifndef STATION_H
#define STATION_H

#include <string>
using namespace std;

class Station {
public:
    Station(string name);
    Station(string name, string district, string municipality, string township, string line);

    const string getName();
    const string getDistrict();
    const string getMunicipality();
    const string getTownship();
    const string getLine();

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
