#include "src/menu.h"

#include <iostream>

<<<<<<< HEAD
void showMenu() {
    cout << "1 - " << endl;
    cout << "2 - " << endl;
    cout << "3 - " << endl;
    cout << "4 - " << endl << endl;

    cout << "0 - Sair" << endl;
}

int main() {
    NetworkManager networkManager;
    networkManager.readFiles();

    bool running = true;
    while (running) {
        showMenu();
        int input;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256,'\n');
            option = 0;
        }
        switch (input) {
            case 1:
                break;
            case 2 :
                break;
            case 3:
                break;
            case 4:
                break;
            case 0:
                running = false;
                break;
            default:
                cout << "[INVALID INPUT]" << endl;
                break;
        }
    }
=======
int readBetweenInt(int low, int high) {
    int input;
    do {
        cout << "Por favor insira um valor entre " << low << " e " << high << endl;
        cin >> input;
    } while (input < low || input > high);
    return input;
}


int main() {
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
>>>>>>> 401acb91568fcfb6a7147f61ddb30eb248914b6f
}