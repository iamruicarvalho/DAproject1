
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "codigo/include/station.h"
#include "codigo/include/network.h"


Station::Station() {

}

std::unordered_map<int,std::string> Station::get_stations_code(){
    return stations_code;
}

std::vector<std::vector<std::string>> Station::get_stations() {
    return stations;
}

void Station::station_reader(){
    int station_count=0;
    std::fstream fin;
    fin.open("../resources/stations.csv", std::ios::in);
    std::vector<std::string> row;
    std::string line, word, temp;
    int i=0;
    while(!fin.eof()){
        row.clear();
        getline(fin,line);
        if(line== "") break;
        std::stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        if (station_count==0){
            station_count++;
            continue;
        }
        i++;
        stations_code[i]=row[0];
        stations.push_back(row);
    }
}
