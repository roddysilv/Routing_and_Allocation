#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
using namespace std;

vector<vector<float>> distancias;
vector<pair<int, int>> nodeCoords;
vector<pair<int, int>> bssCoords;
vector<int> nodeDemands;
int nodeCount, vehicleCapacity, nodeBase, bssCost, bssCount, vehiclesNeeded, totalDemand;
float batteryCapacity;

float distance(int x1, int y1, int x2, int y2);
void saveFile(int carro, vector<int> caminho);
void leitura(ifstream &input_file);
void construtivoGuloso();
void construtivoGulosoRand();
void print();
void twoOpt(vector<int> caminho);
float custo(vector<int> caminho);
vector<int> swap(int i, int j,vector<int> caminho);

int main(int argc, char *argv[])
{
    ifstream input_file(argv[1]);
    vector<pair<int, float>> teste[1];
    leitura(input_file);

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

    construtivoGuloso();
    construtivoGulosoRand();

    //cin.ignore();

    return 0;
}

void twoOpt(vector<int> caminho)
{
    bool aprimorado = true;
    while (aprimorado)
    {
        aprimorado = false;
        for(int i = 1; i < caminho.size() - 2; i++)
        {
            for(int j = i + 1; j < caminho.size(); j++)
            {
                if (j - i == 1)
                {
                    continue;
                }
                vector<int> novoCaminho = swap(i,j,caminho);
                //novoCaminho[i:j] = caminho[j - 1:i - 1:-1]
                if ( custo(novoCaminho) < custo(caminho))
                {
                    caminho = novoCaminho;
                    aprimorado = true;
                }
            }
        }
    }

    for(int i =0; i< caminho.size(); i++)
    {
        cout << caminho[i] << " ";
    }
    cout << endl;

}

vector<int> swap(int i, int j,vector<int> caminho)
{
    vector<int> aux;
    for(int k = j ; k > i; k--)
    {
        aux.push_back(caminho[k]);
    }
    int l = 0;
    for(int k = i ; k <= j; k++)
    {
        caminho[i] = aux[j];
        l++;
    }
    return caminho;
}

float custo(vector<int> caminho)
{
    float custoRota = 0;

    for(int i = 0; i< caminho.size()-1; i++)
    {
        custoRota += distancias[caminho[i]][caminho[i+1]];
    }
    return custoRota;
}

void construtivoGuloso()
{
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoRota;

    vector<int> nosVisitados;
    vector<int> caminho;

    noAtual = nodeBase;
    nosVisitados.push_back(noAtual);
    caminho.push_back(noAtual);

    carros = 0;
    bool atualizado = true; // Booleano que verifica se há candidato para entrar na rota.

    cout << "ROTAS:" << endl << endl;
    while(nosVisitados.size()<distancias.size()) // Enquanto todos os nós não forem visitados.
    {
        custoRota = 0;
        trocasBat = 0;
        auxCapacity = vehicleCapacity;
        auxBat = batteryCapacity;
        carros++;
        cout <<"Rota carro #" << carros << ": " << noAtual;

        while(auxCapacity > 0) // Enquanto o veículo não está cheio (a cada iteração é diminuida a capacidade de carga de acordo com a demanda do cliente).
        {
            atualizado = false;
            custoMin = batteryCapacity;
            for(int j = 0 ; j < distancias.size(); j++)
            {
                // Verifica se a distancia para p proximo cliente é menor, se o nó verificado não é o msmo, se o nó verificado já foi visitado, e se a capacidade do veículo não foi excedida.
                if( distancias[noAtual][j] < custoMin && noAtual != j && find(nosVisitados.begin(), nosVisitados.end(), j) == nosVisitados.end()
                        && auxCapacity - nodeDemands[j] >= 0)
                {
                    custoMin = distancias[noAtual][j];
                    proxNo = j;
                    atualizado = true;
                }
            }

            if(atualizado==false) // Não encontrou próximo cliente que satisfaça as condições.
            {
                break; // Para o algorítmo e não adiciona mais clientes na rota.
            }

            if(auxBat-distancias[noAtual][proxNo] < 0 ) // Troca de bateria.
            {
                trocasBat++;
                auxBat = batteryCapacity;
            }

            auxBat -= distancias[noAtual][proxNo];
            noAtual = proxNo; // Atualiza nó.
            auxCapacity -= nodeDemands[proxNo];
            custoRota += custoMin;
            nosVisitados.push_back(noAtual);
            caminho.push_back(noAtual);
            cout << "->" << noAtual;
        }
        
        saveFile(carros, caminho); // Salva caminho percorrido pelo veículo.
        
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Custo da rota: " << custoRota;
        cout << endl << endl;
        
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
}

void construtivoGulosoRand(){
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoRota;

    vector<int> nosVisitados;
    vector<int> caminho;
    vector<int> candidatos;

    for(int i = 1; i < nodeCount; i++){
        candidatos.push_back(i);
    }
    
    noAtual = nodeBase;
    nosVisitados.push_back(noAtual);
    caminho.push_back(noAtual);

    carros = 0;
    bool atualizado = true; // Booleano que verifica se há candidato para entrar na rota.

    cout << "ROTAS:" << endl << endl;
    
    while(candidatos.size() > 0){
        custoRota = 0;
        trocasBat = 0;
        auxCapacity = vehicleCapacity;
        auxBat = batteryCapacity;
        carros++;
        cout <<"Rota carro #" << carros << ": " << noAtual;

        while(auxCapacity > 0) // Enquanto o veículo não está cheio (a cada iteração é diminuida a capacidade de carga de acordo com a demanda do cliente).
        {
            atualizado = false;
            custoMin = batteryCapacity;
            int test = 0;
            while(test < 200)
            {
                int random = rand() % candidatos.size();
                int rNo = candidatos[random];
                // Verifica se a capacidade do veículo não foi excedida.
                if( auxCapacity - nodeDemands[rNo] >= 0)
                {
                    custoRota += distancias[noAtual][rNo];
                    candidatos.erase(candidatos.begin() + random);
                    atualizado = true;
                    break;
                }
                test++;
            }
            if(atualizado==false) // Não encontrou próximo cliente que satisfaça as condições.
            {
                break; // Para o algorítmo e não adiciona mais clientes na rota.
            }

            if(auxBat-distancias[noAtual][proxNo] < 0 ) // Troca de bateria.
            {
                trocasBat++;
                auxBat = batteryCapacity;
            }

            auxBat -= distancias[noAtual][proxNo];
            noAtual = proxNo; // Atualiza nó.
            auxCapacity -= nodeDemands[proxNo];
            custoRota += custoMin;
            nosVisitados.push_back(noAtual);
            caminho.push_back(noAtual);
            cout << "->" << noAtual;
        }
        
        saveFile(carros, caminho); // Salva caminho percorrido pelo veículo.
        
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Custo da rota: " << custoRota;
        cout << endl << endl;
        
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
}
void leitura(ifstream &input_file)
{
    string line;
    string value;

    // auxiliar variables:
    stringstream ss;
    int aux;

    while(getline(input_file,line) && line != "END_FILE\r")
    {
        if(line == "NODE_COUNT_SECTION\r")
        {
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                nodeCount = stoi(value);
            }
        }
        else if(line == "VEHICLE_CAP_SECTION\r")
        {
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                vehicleCapacity = stoi(value);
            }
        }
        else if(line == "NODE_COORD_SECTION\r")
        {
            pair<int, int> coord;
            int nodeIndex;
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                ss.clear();
                ss << value;
                ss >> nodeIndex;
                ss >> aux;
                coord.first = aux;
                ss >> aux;
                coord.second = aux;
                nodeCoords.push_back(coord);
            }
        }
        else if(line == "NODE_DEMAND_SECTION\r")
        {
            int nodeIndex;
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                ss.clear();
                ss << value;
                ss >> nodeIndex;
                ss >> aux;
                nodeDemands.push_back(aux);
            }
        }
        else if(line == "NODE_BASE_SECTION\r")
        {
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                ss.clear();
                ss << value;
                ss >> nodeBase;
            }
        }
        else if(line == "BATTERY_CAPACITY_SECTION\r")
        {
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                ss.clear();
                ss << value;
                ss >> batteryCapacity;
            }
        }
        else if(line == "CONSTRUCTION_COST_BSS_SECTION\r")
        {
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                ss.clear();
                ss << value;
                ss >> bssCost;
            }
        }
        else if(line == "CANDIDATE_BSS_COUNT_SECTION\r")
        {
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                if(value.empty()) continue;
                ss.clear();
                ss << value;
                ss >> bssCount;
            }
        }
        else if(line == "CANDIDATE_BSS_COORD_SECTION\r")
        {
            pair<int, int> coord;
            int bssIndex;
            while (getline(input_file, value) && value != "END_SECTION\r")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                ss.clear();
                ss << value;
                ss >> bssIndex;
                ss >> aux;
                coord.first = aux;
                ss >> aux;
                coord.second = aux;
                bssCoords.push_back(coord);
            }
        }
    }
    float auxD;
    for(int i = 0; i < nodeCount; i++)
    {
        vector<float> auxV;
        for(int j = 0 ; j <nodeCount; j++)
        {
            auxD = distance(nodeCoords[i].first,nodeCoords[i].second,nodeCoords[j].first,nodeCoords[j].second);
            auxV.push_back(auxD);
            if (auxD > batteryCapacity)
            {
                batteryCapacity = auxD;
            }
        }
        distancias.push_back(auxV);
    }
    batteryCapacity = 1.2 * batteryCapacity;
}

void saveFile(int carro, vector<int> caminho)
{
    string path = ("Arquivos/coordenadas" + to_string(carro) + ".csv");
    ofstream save(path);
    save << "x,y,no" << endl;
    for(int i = 0 ; i < caminho.size(); i++)
    {
        save << nodeCoords[caminho[i]].first << "," << nodeCoords[caminho[i]].second << "," << caminho[i] << endl;
    }
    save.close();
}

float distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void print()
{
    for(int i = 0 ; i < distancias.size(); i++)
    {
        for(int j = 0 ; j < distancias.size(); j++)
        {
            cout << distancias[i][j]<< " ";
        }
        cout << endl;
    }
}
