//
// Created by Bernardo Pinto on 06/03/2023.
//

#include "Network.h"

Network::Network(std::string stationA, std::string stationB)
    : stationA_(stationA), stationB_(stationB) {}

Network::Network(std::string stationA, std::string stationB, double capacity, std::string service)
    : stationA_(stationA),
    stationB_(stationB),
    capacity_(capacity),
    service_(service) {}

const string Network::getStationA() const {
    return stationA_;
}
const string Network::getStationB() const {
    return stationB_;
}
const double Network::getCapacity() const {
    return capacity_;
}
const string Network::getService() const {
    return service_;
}

void Network::setStationA(const std::string stationA) {
    stationA_ = stationA;
}
void Network::setStationB(const std::string stationB) {
    stationB_ = stationB;
}
void Network::setCapacity(const double capacity) {
    capacity_ = capacity;
}
void Network::setService(const std::string service) {
    service_ = service;
}
bool Network::operator<(const Network& network2) const{
    if(stationA_==network2.stationA_){
        return stationB_<network2.stationB_;
    }
    return stationA_<network2.stationA_;
}


