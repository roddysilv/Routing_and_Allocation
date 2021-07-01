#include "functions.h"

using namespace std;

void twoOpt(vector<int> caminho,int carro)
{
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

    if(cInicial == custo(caminho))
    {
        cout << " -> Não houve melhoria para esta rota." << endl <<endl;
    }
    else
    {
        cout << " -> 2opt: ";
        vector<int> vazio;
        imprimeCaminho(caminho,vazio);
        cout << " Novo custo: " << custo(caminho) << endl;
        cout << endl;
        //saveFile(carro,caminho,"2opt");
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

void construtivoGuloso()
{
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoTotal = 0;

    vector<int> nosVisitados;
    vector<int> caminho;

    noAtual = nodeBase;
    nosVisitados.push_back(noAtual);
    caminho.push_back(noAtual);

    carros = 0;
    bool atualizado = true; // Booleano que verifica se há candidato para entrar na rota.

    cout << "===================================================================================" << endl;
    cout << "CONSTRUTIVO GULOSO" << endl;
    cout << "ROTAS:" << endl << endl;
    while(nosVisitados.size()<distancias.size()) // Enquanto todos os nós não forem visitados.
    {
        trocasBat = 0;
        auxCapacity = vehicleCapacity;
        auxBat = batteryCapacity;
        carros++;
        cout <<"Rota carro #" << carros << ": ";

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
                break; // Para o loop e não adiciona mais clientes na rota.
            }

            if(auxBat-distancias[noAtual][proxNo] < 0 ) // Troca de bateria.
            {
                trocasBat++;
                auxBat = batteryCapacity;
            }

            auxBat -= distancias[noAtual][proxNo];
            noAtual = proxNo; // Atualiza nó.
            auxCapacity -= nodeDemands[proxNo];
            nosVisitados.push_back(noAtual);
            caminho.push_back(noAtual);
        }
        if(auxBat-distancias[noAtual][0] < 0 ) // Troca de bateria.
        {
            trocasBat++;
            auxBat = batteryCapacity;
        }
        caminho.push_back(0);
        //saveFile(carros, caminho, "Guloso"); // Salva caminho percorrido pelo veículo.
        vector<int> vazio;
        imprimeCaminho(caminho, vazio);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;

        twoOpt(caminho, carros);

        custoTotal+=custo(caminho);
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
    cout << "Custo Total: " << custoTotal << endl << endl;
}

void construtivoGulosoBuscaEstacao()
{
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoTotal = 0;

    vector<int> estacoes;
    vector<int> nosVisitados;
    vector<int> caminho;

    noAtual = nodeBase;
    nosVisitados.push_back(noAtual);
    caminho.push_back(noAtual);

    carros = 0;
    bool atualizado = true; // Booleano que verifica se há candidato para entrar na rota.

    cout << "===================================================================================" << endl;
    cout << "CONSTRUTIVO GULOSO BUSCA ESTACAO" << endl;
    cout << "ROTAS:" << endl << endl;
    while(nosVisitados.size()<distancias.size()) // Enquanto todos os nós não forem visitados.
    {
        trocasBat = 0;
        auxCapacity = vehicleCapacity;
        auxBat = batteryCapacity;
        carros++;
        cout <<"Rota carro #" << carros << ": ";

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
                break; // Para o loop e não adiciona mais clientes na rota.
            }

            trocaBateria(auxBat, noAtual, estacoes,trocasBat,caminho,proxNo);

            auxBat -= distancias[noAtual][proxNo];
            noAtual = proxNo; // Atualiza nó.
            auxCapacity -= nodeDemands[proxNo];
            nosVisitados.push_back(noAtual);
            caminho.push_back(noAtual);
        }
        trocaBateria(auxBat, noAtual, estacoes,trocasBat,caminho,0);
        caminho.push_back(0);
        saveFile(carros, caminho, "Guloso",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;

        twoOpt(caminho, carros);

        custoTotal+=custo(caminho);
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
    cout << "Custo Total: " << custoTotal << endl << endl;
}

void trocaBateria(float &auxBat, int &noAtual, vector<int> &estacoes, int &trocasBat, vector<int> &caminho, int proxNo)
{
    if(auxBat / batteryCapacity <= 0.3  || auxBat - distancias[noAtual][proxNo]<0)
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
    cout<< "0";
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

void construtivoGulosoRand()
{
    srand(time(0));
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoTotal = 0;

    vector<int> nosVisitados;
    vector<int> caminho;
    vector<int> candidatos;

    for(int i = 1; i < nodeCount; i++)
    {
        candidatos.push_back(i);
    }

    noAtual = nodeBase;
    nosVisitados.push_back(noAtual);
    caminho.push_back(noAtual);

    carros = 0;
    bool atualizado = true; // Booleano que verifica se há candidato para entrar na rota.

    cout << "===================================================================================" << endl;
    cout << "CONSTRUTIVO GULOSO 'RANDOMICO' PURO" << endl;
    cout << "ROTAS:" << endl << endl;

    while(candidatos.size() > 0)
    {
        trocasBat = 0;
        auxCapacity = vehicleCapacity;
        auxBat = batteryCapacity;
        carros++;
        cout <<"Rota carro #" << carros << ": ";

        int maxIt = 0;
        while(auxCapacity > 0 && maxIt < 20 && candidatos.size() > 0) // Enquanto o veículo não está cheio (a cada iteração é diminuida a capacidade de carga de acordo com a demanda do cliente).
        {
            int random = rand() % candidatos.size();
            int rNo = candidatos[random];
            // Verifica se a capacidade do veículo não foi excedida.
            if( auxCapacity - nodeDemands[rNo] >= 0)
            {
                candidatos.erase(candidatos.begin() + random);
                atualizado = true;

                if(auxBat-distancias[noAtual][rNo] < 0 ) // Troca de bateria.
                {
                    trocasBat++;
                    auxBat = batteryCapacity;
                }

                auxBat -= distancias[noAtual][rNo];
                noAtual = rNo; // Atualiza nó.
                auxCapacity -= nodeDemands[rNo];
                nosVisitados.push_back(noAtual);
                caminho.push_back(noAtual);
            }
            maxIt++;
        }

        if(auxBat-distancias[noAtual][0] < 0 ) // Troca de bateria.
        {
            trocasBat++;
            auxBat = batteryCapacity;
        }
        caminho.push_back(0);
        //saveFile(carros, caminho, "Guloso"); // Salva caminho percorrido pelo veículo.
        vector<int> vazio;
        imprimeCaminho(caminho, vazio);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;

        twoOpt(caminho, carros);

        custoTotal+=custo(caminho);
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
    cout << "Custo Total: " << custoTotal << endl << endl;
}

/*void construtivoGulosoRandPARAMETRIZADO(){
    srand(time(0));
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoRota, custoTotal = 0;

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

    cout << "===================================================================================" << endl;
    cout << "CONSTRUTIVO GULOSO 'RANDOMICO' PARAMETRIZADO" << endl;
    cout << "ROTAS:" << endl << endl;

    while(candidatos.size() > 0){
        custoRota = 0;
        trocasBat = 0;
        auxCapacity = vehicleCapacity;
        auxBat = batteryCapacity;
        carros++;
        cout <<"Rota carro #" << carros << ": " << noAtual;

        int maxIt =0;
        while(auxCapacity > 0 && maxIt < 20 && candidatos.size() > 0) // Enquanto o veículo não está cheio (a cada iteração é diminuida a capacidade de carga de acordo com a demanda do cliente).
        {
            int random = rand() % candidatos.size();
            int rNo = candidatos[random];
            //cout << random <<" "<< rNo<< endl;
            // Verifica se a capacidade do veículo não foi excedida.
            if( auxCapacity - nodeDemands[rNo] >= 0)
            {
                custoRota += distancias[noAtual][rNo];
                candidatos.erase(candidatos.begin() + random);
                atualizado = true;

                if(auxBat-distancias[noAtual][rNo] < 0 ) // Troca de bateria.
                {
                    trocasBat++;
                    auxBat = batteryCapacity;
                }

                auxBat -= distancias[noAtual][rNo];
                noAtual = rNo; // Atualiza nó.
                auxCapacity -= nodeDemands[rNo];
                custoRota += custoMin;
                nosVisitados.push_back(noAtual);
                caminho.push_back(noAtual);
                cout << "->" << noAtual;
            }
            maxIt++;
        }

        saveFile(carros, caminho, "GulosoRand"); // Salva caminho percorrido pelo veículo.

        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Custo da rota: " << custoRota;
        cout << endl << endl;

        custoTotal+=custoRota;
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
    cout << "Custo Total: " << custoTotal << endl << endl;
}*/

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
