

#include <iostream>
#include "src/NetworkManager.h"

void showMenu() {
    cout << "1 - Pretendo saber o fluxo maximo de comboios entre 2 estações" << endl;
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
            cin.ignore(256, '\n');
            int option = 0;
        }
        switch (input) {
            case 1: {
                string first, second;
                cout << "Qual e a primeira estacao?" << endl;
                cin.ignore();
                getline(cin,first);
                cout << "Qual e a segunda estacao?" << endl;
                getline(cin,second);
                int result = networkManager.max_trains(first, second, true);
                if (result == 0) { // quando dá 0 significa que não existe um caminho entre as duas estações
                    cout << "Nao existe um caminho entre essas 2 estacoes" << endl;
                } else {
                    cout << "No maximo, entre essas duas estacoes, podem passar " << result << "comboios ao mesmo tempo"
                         << endl;
                }
                break;
            }
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
}


int readBetweenInt(int low, int high) {
    int input;
    do {
        cout << "Por favor insira um valor entre " << low << " e " << high << endl;
        cin >> input;
    } while (input < low || input > high);
    return input;
}

