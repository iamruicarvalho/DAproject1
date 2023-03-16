//
// Created by David Castro on 13/03/2023.
//

#include "Menu.h"
int Menu::readBetweenInt(int low, int high) {
    int input;
    do {
        cout << "Por favor insira um valor entre " << low << " e " << high << endl;
        cin >> input;
    } while (input < low || input > high);
    return input;
}
Menu::Menu(){
    /*
    this->network = networkManager.getNetwork();
    this->graph = networkManager.getGraph();            Quando o manager estiver terminado ja esta
    this->station = networkManager.getStations();
     */
}
void Menu::mainMenu() {
    int input;
    do{
        cout << "---------------------------- DA TP 1 -----------------------------" << endl;
        cout << "1 - " << endl;
        cout << "2 - " << endl;
        cout << "3 - " << endl;
        cout << "4 - " << endl << endl;

        cout << "0 - Sair" << endl;

        input = readBetweenInt(0, 4);

        switch (input) {
            case 1 : {

            } break;

            case 2 : {

            } break;

            case 3: {

            } break;

            case 4 : {

            }break;

            default: input = 0; break;
        }
    }while(input!=0);
}