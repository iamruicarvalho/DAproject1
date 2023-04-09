//
// Created by Utilizador on 11/03/2023.
//

#include "Station.h"
/**
 * Construtor de uma estação
 * @param name string, nome da estação
 */
Station::Station(string name)
    : name_(name) {}

    /**
     * Construtor de uma estação
     * @param name string, nome da estação
     * @param district string, distrito da estação
     * @param municipality string, município da estação
     * @param township string, cidade da estação
     * @param line string, linha da estação
     */
Station::Station(string name, string district, string municipality, string township, string line)
    : name_(name),
    district_(district),
    municipality_(municipality),
    township_(township),
    line_(line) {}
/**
 * Retorna o nome da estação
 * Complexidade: O(1)
 * @return string, nome da estação
 */
const string Station::getName() const {
    return name_;
}
/**
 * Retorna o distrito da estação
 * Complexidade: O(1)
 * @return string, distrito da estação
 */
const string Station::getDistrict() const {
    return district_;
}
/**
 * Retorna o município da estação
 * Complexidade: O(1)
 * @return string, município da estação
 */
const string Station::getMunicipality() const {
    return municipality_;
}
/**
 * Retorna a cidade da estação
 * Complexidade: O(1)
 * @return string, cidade da estação
 */
const string Station::getTownship() const {
    return township_;
}
/**
 * Retorna a linha da estação
 * Complexidade: O(1)
 * @return string, linha da estação
 */
const string Station::getLine() const {
    return line_;
}
/**
 * Altera o nome da estação
 * Complexidade: O(1)
 * @param name string, nome da estação
 */
void Station::setName(const string name) {
    name_ = name;
}
/**
 * Altera o distrito da estação
 * Complexidade: O(1)
 * @param district string, distrito da estação
 */
void Station::setDistrict(const string district) {
    district_ = district;
}
/**
 * Altera o município da estação
 * Complexidade: O(1)
 * @param municipality string, município da estação
 */
void Station::setMunicipality(const string municipality) {
    municipality_ = municipality;
}
/**
 * Altera a cidade da estação
 * Complexidade: O(1)
 * @param township string, cidade da estação
 */
void Station::setTownship(const string township) {
    township_ = township;
}
/**
 * Altera a linha da estação
 * Complexidade: O(1)
 * @param line string, linha da estação
 */
void Station::setLine(const string line) {
    line_ = line;
}
/**
 * Compara duas estações
 * Complexidade: O(1)
 * @param station2 Station, estação a comparar
 * @return bool, true se a estação for menor que a estação 2
 */
bool Station::operator<(const Station& station2) const{
    return this->name_< station2.name_;
}