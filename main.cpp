

#include <iostream>
#include "src/NetworkManager.h"
#include <locale.h>
#include <codecvt>


void showMenu() {
    cout << "1 - Pretendo saber o fluxo maximo de comboios entre 2 estações" << endl;
    cout << "2 - Pretendo saber qual é o máximo valor possível de fluxo entre 2 estações quaisquer" << endl;
    cout << "3 - 2.3" << endl; // nao sei que nome colocar
    cout << "4 - " << endl << endl;
    cout << "5 - See how many trains can arrive at a specific station" << endl;
    cout << "6 - " << endl;
    cout << "7 - Desejo reportar um troço do caminho de ferro que não está operacional" << endl;
    cout << "8 - Desejo reportar um troço do caminho de ferro que já está operacional" << endl;
    cout << "9 - Pretendo saber o fluxo maximo de comboios entre 2 estações, tendo em conta as linhas que foram cortadas " << endl << endl;

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
                getline(cin, first);
                cout << "Qual e a segunda estacao?" << endl;
                getline(cin, second);
                int result = networkManager.max_trains(first, second);
                if (result == -1) {
                    cout << "Erro ao ler as estações submetidas" << endl;
                } else if (result == 0) { // quando dá 0 significa que não existe um caminho entre as duas estações
                    cout << "Nao existe um caminho entre essas 2 estações" << endl;
                } else {
                    cout << "No máximo, entre essas duas estacoes, podem passar " << result
                         << " comboios ao mesmo tempo"
                         << endl;
                }
                break;
            }
            case 2 :{
                pair<int,pair<string,string>> result= networkManager.max_of_max_trains();
                cout << "Entre " << result.second.first << " e " <<result.second.second<< ", que corresponde à ligação com maior fluxo possível, podem passar "<<
                                    result.first <<" comboios ao mesmo tempo." << endl;
                break;
            }
            case 3:
                cout << "1 - Pretendo saber qual o concelho que necessita de mais comboios" << endl;
                cout << "2 - Pretendo saber qual o municipio que necessita de mais comboios" << endl;
                cout << "3 - Pretendo saber qual o distrito que necessita de mais comboios" << endl;
                int n;
                cin >> n;
                switch (n) {
                    case 1:
                        int k;
                        cin >> k;
                        networkManager.trainManagementByTownship(k);
                        break;
                    case 2:
                        cin >> k;
                        networkManager.trainManagementByMunicipality(k);
                        break;
                    case 3:
                        cin >> k;
                        networkManager.trainManagementByDistrict(k);
                        break;
                }
                break;
            case 4:
                break;
            case 5: {
                string station;
                cin >> station;
                int result = networkManager.maxTrainsArrivingAtStation(station);
                cout << result << endl;
                break;
            }
            case 6:
                break;
            case 7: {
                string first, second;
                cout << "Qual é a primeira estação do troço que deseja cortar?" << endl;
                cin.ignore();
                getline(cin, first);
                cout << "Qual é a segunda estação do troço que deseja cortar?" << endl;
                getline(cin, second);
                bool found= networkManager.set_block(first,second);
                if(found){
                    cout<< "Bloqueio feito entre essas 2 estações realizado com sucesso" << endl;
                }
                else{
                    cout<< "Não foi encontrado um troço que conecte diretamente essas 2 estações" << endl;
                }
                break;
            }
            case 8: {
                string first, second;
                cout << "Qual é a primeira estação do bloqueio que deseja remover?" << endl;
                cin.ignore();
                getline(cin, first);
                cout << "Qual é a segunda estação do bloqueio que deseja remover?" << endl;
                getline(cin, second);
                bool found = networkManager.remove_block(first, second);
                if(found){
                    cout<< "Bloqueio removido entre essas 2 estações realizado com sucesso" << endl;
                }
                else{
                    cout<< "Não foi encontrado um troço que conecte diretamente essas 2 estações" << endl;
                }
                break;
            }
            case 9:
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



