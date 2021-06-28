#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "functions.h"

using namespace std;

///Variáveis
vector<vector<float>> distancias;
vector<pair<int, int>> nodeCoords;
vector<pair<int, int>> bssCoords;
vector<int> nodeDemands;
int nodeCount, vehicleCapacity, nodeBase, bssCost, bssCount, vehiclesNeeded, totalDemand;
float batteryCapacity;

int main(int argc, char *argv[])
{
    ifstream input_file(argv[1]);
    int algContrutivo = atoi(argv[2]);
    vector<pair<int, float>> teste[1];
    #ifdef _WIN32
        leituraWin(input_file);
    #else
        leitura(input_file);
    #endif

    totalDemand = accumulate(nodeDemands.begin(), nodeDemands.end(), 0);
    vehiclesNeeded = ceil((float)(totalDemand)/vehicleCapacity);

    cout << "INFO:"<<endl;
    cout << endl << "Capacidade da bateria do veiculo: " << batteryCapacity << endl ;
    cout << "Custo da troca de bateria: " << bssCost << endl;
    cout << "Capacidade de transporte do veiculo: " << vehicleCapacity << endl ;
    cout << "Demanda total: " << totalDemand << endl;
    cout << "Quantidade minima de veiculos necessarios: " << vehiclesNeeded << endl;
    cout << "Quantidade de clientes: " << nodeCount - 1 << endl << endl;

    //print();

    if(algContrutivo == 1)
    {
        construtivoGuloso();
    }
    if(algContrutivo == 2)
    {
        construtivoGulosoRand();
    }

    //cin.ignore();

    return 0;
}
