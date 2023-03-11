//
// Created by Utilizador on 11/03/2023.
//

#include "Station.h"

Station::Station(int name)
    : name_(name) {}

Station::Station(int name, int district, int municipality, int township, int line)
    : name_(name),
    district_(district),
    municipality_(municipality),
    township_(township),
    line_(line) {}

const string Station::getName() {
    return name_;
}
const string Station::getDistrict() {
    return district_;
}
const string Station::getMunicipality() {
    return municipality_;
}
const string Station::getTownship() {
    return township_;
}
const string Station::getLine() {
    return line_;
}
const void Station::setName(const int name) {
    name_ = name;
}
const void Station::setDistrict(const int district) {
    district_ = district;
}
const void Station::setMunicipality(const int municipality) {
    municipality_ = municipality;
}
const void Station::setTownship(const int township) {
    township_ = township;
}
const void Station::setLine(const int line) {
    line_ = line;
}