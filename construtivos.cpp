#include "auxFunc.h"
#include "construtivos.h"

void construtivoGuloso()
{
    auto start = high_resolution_clock::now();

    int noAtual,proxNo, auxCapacity, carros, trocasBat, est=0;
    float custoMin, auxBat, custoTotal = 0,custoTotalBusca = 0;

    vector<vector<int>> rotas;

    vector<int> nosVisitados;
    vector<int> caminho;
    vector<int> estacoes;

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
                estacoes.push_back(noAtual);
                trocasBat++;
                auxBat = batteryCapacity;
            }

            auxBat -= distancias[noAtual][proxNo];
            noAtual = proxNo; // Atualiza nó.
            auxCapacity -= nodeDemands[proxNo];
            nosVisitados.push_back(noAtual);
            caminho.push_back(noAtual);
        }
        if(auxBat-distancias[noAtual][nodeBase] < 0 ) // Troca de bateria.
        {
            estacoes.push_back(noAtual);
            trocasBat++;
            auxBat = batteryCapacity;
        }
        est+=trocasBat;
        caminho.push_back(nodeBase);
        saveFile(carros, caminho, "Guloso",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;
        estacoes.clear();

        custoTotal+=custo(caminho) + (trocasBat * bssCost);
        rotas.push_back(caminho);

        caminho = {nodeBase}; // Ajusta caminho para o pŕoximo veículo
        noAtual = nodeBase;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;

    start = high_resolution_clock::now();
    cout << "2opt" << endl << endl;
    for(int i = 0; i< rotas.size(); i++)
    {
        custoTotalBusca += twoOpt(rotas[i], i);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;

    cout << "Custo Total: " << custoTotal  << endl;
    cout << "Estacoes criadas: " << est << endl;
    cout << "Custo Total Busca Local: " << custoTotalBusca << endl << endl;
}

void construtivoGulosoRand()
{
    auto start = high_resolution_clock::now();

    srand(time(0));
    int noAtual,proxNo, auxCapacity, carros, trocasBat,est=0;
    float custoMin, auxBat, custoTotal = 0,custoTotalBusca = 0;

    vector<vector<int>> rotas;

    vector<int> nosVisitados;
    vector<int> caminho;
    vector<int> candidatos;
    vector<int> estacoes;

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
                    estacoes.push_back(noAtual);
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

        if(auxBat-distancias[noAtual][nodeBase] < 0 ) // Troca de bateria.
        {
            estacoes.push_back(noAtual);
            trocasBat++;
            auxBat = batteryCapacity;
        }
        caminho.push_back(nodeBase);
        saveFile(carros, caminho, "GulosoRand",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;
        estacoes.clear();

        custoTotal+=custo(caminho)+ (trocasBat * bssCost);
        rotas.push_back(caminho);

        caminho = {nodeBase}; // Ajusta caminho para o pŕoximo veículo
        noAtual = nodeBase;
        est += trocasBat;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;

    start = high_resolution_clock::now();
    cout << "2opt" << endl << endl;
    for(int i = 0; i< rotas.size(); i++)
    {
        custoTotalBusca += twoOpt(rotas[i], i+1);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;

    cout << "Custo Total: " << custoTotal  << endl;
    cout << "Estacoes criadas: " << est << endl;
    cout << "Custo Total Busca Local: " << custoTotalBusca << endl << endl;
}

void construtivoGulosoBuscaEstacao(float percent)
{
    auto start = high_resolution_clock::now();

    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoTotal = 0, custoTotalBusca = 0;

    vector<vector<int>> rotas;

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
                // Verifica se a distancia para p proximo cliente é menor, se o nó verificado não é o mesmo, se o nó verificado já foi visitado, e se a capacidade do veículo não foi excedida.
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

            trocaBateria(percent, auxBat, noAtual, estacoes,trocasBat,caminho,proxNo);

            auxBat -= distancias[noAtual][proxNo];
            noAtual = proxNo; // Atualiza nó.
            auxCapacity -= nodeDemands[proxNo];
            nosVisitados.push_back(noAtual);
            caminho.push_back(noAtual);
        }
        trocaBateria(percent, auxBat, noAtual, estacoes,trocasBat,caminho,0);
        caminho.push_back(nodeBase);
        saveFile(carros, caminho, "GulosoBusca",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;

        custoTotal+=custo(caminho)+ (estacoes.size() * bssCost);
        rotas.push_back(caminho);
        caminho = {nodeBase}; // Ajusta caminho para o pŕoximo veículo
        noAtual = nodeBase;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;

    start = high_resolution_clock::now();
    cout << "2opt" << endl << endl;
    for(int i = 0; i< rotas.size(); i++)
    {
        custoTotalBusca += twoOpt2(rotas[i], i, estacoes);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duracao da execucao: " << duration.count() << " microsegundos" << endl << endl;

    cout << "Custo Total: " << custoTotal << endl;
    cout << "Estacoes Criadas: " << estacoes.size() << endl;
    cout << "Custo Total Busca Local: " << custoTotalBusca << endl << endl;
}
