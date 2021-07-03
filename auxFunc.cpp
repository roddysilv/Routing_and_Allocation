#include "auxFunc.h"

using namespace std;

void twoOpt(vector<int> caminho,int carro)
{
    vector<int> estacoes;
    float cInicial = custo(caminho);
    bool aprimorado = true;
    while (aprimorado)
    {
        aprimorado = false;
        for(int i = 1; i < caminho.size() - 2; i++)
        {
            for(int j = i + 1; j < caminho.size()-1; j++)
            {
                vector<int> novoCaminho = swap(i,j,caminho);
                if ( custo(novoCaminho) < custo(caminho))
                {
                    caminho = novoCaminho;
                    aprimorado = true;
                }   
            }
        }
    }

    float auxBat = batteryCapacity;
    for(int i = 0 ; i < caminho.size()-1; i++){
        if(auxBat - distancias[caminho[i]][caminho[i+1]]<0){
            estacoes.push_back(caminho[i]);
            auxBat = batteryCapacity;
        }
        auxBat -= distancias[caminho[i]][caminho[i+1]];
    }

    cout << "2opt:" << endl;
    if(cInicial == custo(caminho))
    {
        cout << "Não houve melhoria para esta rota." << endl <<endl;
    }
    else
    {
        imprimeCaminho(caminho,estacoes);
        cout << " Novo custo: " << custo(caminho) << endl;
        cout << endl;
        saveFile(carro,caminho,"2opt",estacoes);
    }
}

void twoOpt2(vector<int> caminho,int carro, vector<int> estacoes)
{
    int est = 0;
    for(int i = 1; i< caminho.size()-1;i++){
        if(find(estacoes.begin(), estacoes.end(), caminho[i]) != estacoes.end()){
            est++;
        }
    }
    cout << est;

    float cInicial = custo(caminho);
    bool aprimorado = true;
    while (aprimorado)
    {
        aprimorado = false;
        for(int i = 1; i < caminho.size() - 2; i++)
        {
            for(int j = i + 1; j < caminho.size()-1; j++)
            {
                vector<int> novoCaminho = swap(i,j,caminho);
                if ( custo(novoCaminho) < custo(caminho))
                {
                    caminho = novoCaminho;
                    aprimorado = true;
                }   
            }
        }
    }
    cout << "2opt:" << endl;
    if(cInicial == custo(caminho))
    {
        cout << "Não houve melhoria para esta rota." << endl <<endl;
    }
    else
    {
        imprimeCaminho(caminho,estacoes);
        cout << " Novo custo: " << custo(caminho) << endl;
        cout << endl;
        saveFile(carro,caminho,"2opt",estacoes);
    }
}

vector<int> swap(int a, int b,vector<int> caminho)
{
    vector<int> aux;
    for(int i = b ; i >= a; i--)
    {
        aux.push_back(caminho[i]);
    }
    int l = 0;
    for(int i = a ; i <= b; i++)
    {
        caminho[i] = aux[l];
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

void trocaBateria(float percent, float &auxBat, int &noAtual, vector<int> &estacoes, int &trocasBat, vector<int> &caminho, int proxNo)
{
    if(auxBat / batteryCapacity <= percent || auxBat - distancias[noAtual][proxNo]<0)
    {
        if(estacoes.size() == 0)
        {
            estacoes.push_back(noAtual);
        }
        else
        {
            float aux = batteryCapacity;
            int no=-1;
            for(int i = 0; i < estacoes.size(); i++)
            {
                if(distancias[noAtual][estacoes[i]] < aux && distancias[noAtual][estacoes[i]] <= auxBat)
                {
                    aux = distancias[noAtual][estacoes[i]];
                    no = estacoes[i];
                }
            }
            if(no != -1)
            {
                noAtual = no; // Atualiza nó.
                caminho.push_back(noAtual);
            }
            else
            {
                estacoes.push_back(noAtual);
            }
        }
        trocasBat++;
        auxBat = batteryCapacity;
    }
}

void imprimeCaminho(vector<int> caminho, vector<int> estacoes)
{
    cout<< caminho[0];
    for(int i = 1; i < caminho.size(); i++)
    {
        if(find(estacoes.begin(), estacoes.end(), caminho[i]) != estacoes.end())
        {
            cout << "->" << caminho[i] << "E";
        }
        else
        {
            cout << "->" << caminho[i];
        }
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

void leituraWin(ifstream &input_file)
{
    string line;
    string value;

    // auxiliar variables:
    stringstream ss;
    int aux;

    while(getline(input_file,line) && line != "END_FILE")
    {
        if(line == "NODE_COUNT_SECTION")
        {
            while (getline(input_file, value) && value != "END_SECTION")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                nodeCount = stoi(value);
            }
        }
        else if(line == "VEHICLE_CAP_SECTION")
        {
            while (getline(input_file, value) && value != "END_SECTION")
            {
                if ( !value.empty() && value[value.size()-1] == '\r' )
                {
                    value = value.substr(0, value.size() - 1);
                }
                vehicleCapacity = stoi(value);
            }
        }
        else if(line == "NODE_COORD_SECTION")
        {
            pair<int, int> coord;
            int nodeIndex;
            while (getline(input_file, value) && value != "END_SECTION")
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
        else if(line == "NODE_DEMAND_SECTION")
        {
            int nodeIndex;
            while (getline(input_file, value) && value != "END_SECTION")
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
        else if(line == "NODE_BASE_SECTION")
        {
            while (getline(input_file, value) && value != "END_SECTION")
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
        else if(line == "BATTERY_CAPACITY_SECTION")
        {
            while (getline(input_file, value) && value != "END_SECTION")
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
        else if(line == "CONSTRUCTION_COST_BSS_SECTION")
        {
            while (getline(input_file, value) && value != "END_SECTION")
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
        else if(line == "CANDIDATE_BSS_COUNT_SECTION")
        {
            while (getline(input_file, value) && value != "END_SECTION")
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
        else if(line == "CANDIDATE_BSS_COORD_SECTION")
        {
            pair<int, int> coord;
            int bssIndex;
            while (getline(input_file, value) && value != "END_SECTION")
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

void saveFile(int carro, vector<int> caminho, string algoritmo, vector<int> estacoes)
{
    string path = ("Arquivos/coordenadas" + algoritmo + "_" + to_string(carro) + ".csv");
    ofstream save(path);
    save << "x,y,no,estacao" << endl;
    for(int i = 0 ; i < caminho.size(); i++)
    {
        if(find(estacoes.begin(), estacoes.end(), caminho[i]) != estacoes.end())
        {
            save << nodeCoords[caminho[i]].first << "," << nodeCoords[caminho[i]].second << "," << caminho[i] << ",1" << endl;
        }

        else
        {
            save << nodeCoords[caminho[i]].first << "," << nodeCoords[caminho[i]].second << "," << caminho[i] << ",0" << endl;
        }
    }
    save.close();
}

float distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void printMatrix()
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