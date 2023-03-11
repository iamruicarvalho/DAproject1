//
// Created by Bernardo Pinto on 04/03/2023.
//

#ifndef PROJETO1_STATION_H
#define PROJETO1_STATION_H

#include <vector>

class Station{
public:
    Station();
    void station_reader();
    std::unordered_map<int,std::string> get_stations_code();
    std::vector<std::vector<std::string>> get_stations();
private:
    std::vector<std::vector<std::string>> stations;
    std::unordered_map<int,std::string> stations_code;
};

#endif //PROJETO1_STATION_H
