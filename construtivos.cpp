#include "auxFunc.h"
#include "construtivos.h"

void construtivoGuloso()
{
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoTotal = 0;

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
        caminho.push_back(nodeBase);
        saveFile(carros, caminho, "Guloso",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;
        estacoes.clear();
        
        twoOpt(caminho, carros);

        custoTotal+=custo(caminho);
        caminho = {nodeBase}; // Ajusta caminho para o pŕoximo veículo
        noAtual = nodeBase;
    }
    cout << "Custo Total: " << custoTotal << endl << endl;
}

void construtivoGulosoRand()
{
    srand(time(0));
    int noAtual,proxNo, auxCapacity, carros, trocasBat;
    float custoMin, auxBat, custoTotal = 0;

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
        saveFile(carros, caminho, "Guloso",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;

        twoOpt(caminho, carros);

        custoTotal+=custo(caminho);
        caminho = {nodeBase}; // Ajusta caminho para o pŕoximo veículo
        noAtual = nodeBase;
    }
    cout << "Custo Total: " << custoTotal << endl << endl;
}

void construtivoGulosoBuscaEstacao(float percent)
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
        caminho.push_back(0);
        saveFile(carros, caminho, "Guloso",estacoes); // Salva caminho percorrido pelo veículo.
        imprimeCaminho(caminho, estacoes);
        cout << endl << "Capacidade restante: " << auxCapacity << endl;
        cout << "Capacidade restante da bateria atual: " << auxBat<<endl;
        cout << "Trocas de bateria: " << trocasBat << endl;
        cout << "Custo da rota: " << custo(caminho);
        cout << endl << endl;

        //twoOpt(caminho, carros,estacoes);

        custoTotal+=custo(caminho);
        caminho = {0}; // Ajusta caminho para o pŕoximo veículo
        noAtual = 0;
    }
    cout << "Custo Total das Rotas: " << custoTotal << endl;
    cout << "Estacoes criadas: " << estacoes.size() << endl ;
    cout << "Custo Total: " << custoTotal + estacoes.size()<< endl<< endl;
}