//
// Created by Bernardo Pinto on 04/03/2023.
//

#ifndef PROJETO1_MENU_H
#define PROJETO1_MENU_H

#include "../data_structures/Graph.h"
#include "network.h"

class Menu{
public:
    Menu();
private:
    Graph network = Network().get_network();
};

#endif //PROJETO1_MENU_H
