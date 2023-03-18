//
// Created by Utilizador on 11/03/2023.
//

#include "Station.h"

Station::Station(string name)
    : name_(name) {}

Station::Station(string name, string district, string municipality, string township, string line)
    : name_(name),
    district_(district),
    municipality_(municipality),
    township_(township),
    line_(line) {}

const string Station::getName() const {
    return name_;
}
const string Station::getDistrict() const {
    return district_;
}
const string Station::getMunicipality() const {
    return municipality_;
}
const string Station::getTownship() const {
    return township_;
}
const string Station::getLine() const {
    return line_;
}

void Station::setName(const string name) {
    name_ = name;
}
void Station::setDistrict(const string district) {
    district_ = district;
}
void Station::setMunicipality(const string municipality) {
    municipality_ = municipality;
}
void Station::setTownship(const string township) {
    township_ = township;
}
void Station::setLine(const string line) {
    line_ = line;
}