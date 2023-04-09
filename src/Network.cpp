//
// Created by Bernardo Pinto on 06/03/2023.
//

#include "Network.h"
/**
 * Contrutor de uma ligação entre duas estações
 * @param stationA string, nome da estação A
 * @param stationB string, nome da estação B
 */
Network::Network(std::string stationA, std::string stationB)
    : stationA_(stationA), stationB_(stationB) {}
/**
 * Contrutor de uma ligação entre duas estações tendo em conta a capacidade e o serviço
 * @param stationA string, nome da estação A
 * @param stationB string, nome da estação B
 * @param capacity double, capacidade da ligação
 * @param service string, serviço da ligação
 */
Network::Network(std::string stationA, std::string stationB, double capacity, std::string service)
    : stationA_(stationA),
    stationB_(stationB),
    capacity_(capacity),
    service_(service) {}
/**
 * Retorna o nome da estação A
 * Complexidade: O(1)
 * @return string, nome da estação A
 */
const string Network::getStationA() const {
    return stationA_;
}
/**
 * Retorna o nome da estação B
 * Complexidade: O(1)
 * @return string, nome da estação B
 */
const string Network::getStationB() const {
    return stationB_;
}
/**
 * Retorna a capacidade da ligação
 * Complexidade: O(1)
 * @return double, capacidade da ligação
 */
const double Network::getCapacity() const {
    return capacity_;
}
/**
 * Retorna o serviço da ligação
 * Complexidade: O(1)
 * @return string, serviço da ligação
 */
const string Network::getService() const {
    return service_;
}
/**
 * Altera o nome da estação A
 * Complexidade: O(1)
 * @param stationA string, nome da estação A
 */
void Network::setStationA(const std::string stationA) {
    stationA_ = stationA;
}
/**
 * Altera o nome da estação B
 * Complexidade: O(1)
 * @param stationB string, nome da estação B
 */
void Network::setStationB(const std::string stationB) {
    stationB_ = stationB;
}
/**
 * Altera a capacidade da ligação
 * Complexidade: O(1)
 * @param capacity double, capacidade da ligação
 */
void Network::setCapacity(const double capacity) {
    capacity_ = capacity;
}
/**
 * Altera o serviço da ligação
 * Complexidade: O(1)
 * @param service string, serviço da ligação
 */
void Network::setService(const std::string service) {
    service_ = service;
}
/**
 * Compara duas ligações entre estações
 * @param network2 Network, ligação a comparar
 * @return bool, true se a ligação for menor que a ligação a comparar, false caso contrário
 */
bool Network::operator<(const Network& network2) const{
    if(stationA_==network2.stationA_){
        return stationB_<network2.stationB_;
    }
    return stationA_<network2.stationA_;
}


