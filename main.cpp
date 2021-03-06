#include "auxFunc.h"
#include "construtivos.h"
#include "script.h"
//#include "auxFunc.cpp"
//#include "construtivos.cpp"
//#include "script.cpp"

using namespace std;

//Variáveis
vector<vector<float>> distancias;
vector<pair<int, int>> nodeCoords;
vector<pair<int, int>> bssCoords;
vector<int> nodeDemands;
int nodeCount, vehicleCapacity, nodeBase, bssCost, bssCount, vehiclesNeeded, totalDemand;
float batteryCapacity;

int main(int argc, char *argv[])
{
    /*ifstream input_file(argv[1]);
    int algContrutivo = atoi(argv[2]);
    float percent = stof(argv[3]);
    #ifdef _WIN32
    leituraWin(input_file);
    #else
    leitura(input_file);
    #endif

    totalDemand = accumulate(nodeDemands.begin(), nodeDemands.end(), 0);
    vehiclesNeeded = ceil((float)(totalDemand)/vehicleCapacity);

    cout << "INFO:"<<endl;
    cout << endl << "Capacidade da bateria do veiculo: " << batteryCapacity << endl ;
    cout << "Custo de Criacao de Estacao: " << bssCost << endl;
    cout << "Capacidade de transporte do veiculo: " << vehicleCapacity << endl ;
    cout << "Demanda total: " << totalDemand << endl;
    cout << "Quantidade minima de veiculos necessarios: " << vehiclesNeeded << endl;
    cout << "Quantidade de clientes: " << nodeCount - 1 << endl << endl;

    if(algContrutivo == 1)
    {
        construtivoGuloso();
    }
    else if(algContrutivo == 2)
    {
        auto start = high_resolution_clock::now();
        construtivoGulosoRand();
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;
    }
    else if(algContrutivo == 3)
    {
        auto start = high_resolution_clock::now();
        construtivoGulosoBuscaEstacao(percent);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;
    }*/

    run();

    return 0;
}
