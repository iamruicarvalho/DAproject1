

#include <iostream>
#include "src/NetworkManager.h"
#include <locale.h>
#include <codecvt>


void showMenu() {
    cout << "1 - Pretendo saber o fluxo maximo de comboios entre 2 estações" << endl;
    cout << "2 - Pretendo saber qual é o máximo valor possível de fluxo entre 2 estações quaisquer" << endl;
    cout << "3 - 2.3" << endl; // nao sei que nome colocar
    cout << "4 - " << endl << endl;

    cout << "0 - Sair" << endl;
}

int main() {
    std::locale::global(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    setlocale(LC_ALL, "Portuguese");

    NetworkManager networkManager;
    cout << "[LOADING FILES]" << endl;
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
                int result = networkManager.max_trains(first, second,0, true);
                if (result == -1){
                    cout << "Erro ao ler as estações submetidas" << endl;
                }
                else if (result == 0) { // quando dá 0 significa que não existe um caminho entre as duas estações
                    cout << "Nao existe um caminho entre essas 2 estações" << endl;
                } else {
                    cout << "No máximo, entre essas duas estacoes, podem passar " << result << " comboios ao mesmo tempo"
                         << endl;
                }
                break;
            }
            case 2 :{
                int result= networkManager.max_of_max_trains();
                cout << "No máximo, entre 2 estações quaisquer, podem passar " << result <<" comboios ao mesmo tempo"
                        << endl;
                break;
            }

            case 3:
                cout << "1 - Pretendo saber qual o concelho que necessita de mais combios" << endl;
                cout << "2 - Pretendo saber qual o municipio que necessita de mais combios" << endl;
                cout << "3 - Pretendo saber qual o distrito que necessita de mais combios" << endl;
                int n;
                cin >> n;
                switch (n) {
                    case 1:
                        int k;
                        cin >> k;
                        networkManager.trainManagementByMunicipality(k);
                        break;
                    case 2:
                        cin >> k;
                        networkManager.trainManagementByDistrict(k);
                        break;
                    default:
                        cout << "[INVALID INPUT]" << endl;
                        break;
                }
                break;
            case 4:
                networkManager.max_of_max_trains_with_block("Linha do Minho");
                break;
            case 0:
                running = false;
                break;
            default:
                cout << "[INVALID INPUT]" << endl;
                break;
        }
    }
    return 0;
}



