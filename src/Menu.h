//
// Created by David Castro on 13/03/2023.
//

#ifndef PROJECTDA1_MENU_H
#define PROJECTDA1_MENU_H


#include "NetworkManager.h"

class Menu {
private:
    NetworkManager networkManager;
    Network network; // uma array ou algo do genero depois
    Station station;
    Graph graph;
public:
    Menu();
    int readBetweenInt(int low, int high);
    void mainMenu();
};


#endif //PROJECTDA1_MENU_H
