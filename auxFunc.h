#ifndef AUXFUNC_H_INCLUDED
#define AUXFUNC_H_INCLUDED

#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

extern vector<vector<float>> distancias;
extern vector<pair<int, int>> nodeCoords;
extern vector<pair<int, int>> bssCoords;
extern vector<int> nodeDemands;
extern int nodeCount, vehicleCapacity, nodeBase, bssCost, bssCount, vehiclesNeeded, totalDemand;
extern float batteryCapacity;

float distance(int x1, int y1, int x2, int y2);
void saveFile(int carro, vector<int> caminho, string algoritmo, vector<int> estacoes);
void leitura(ifstream &input_file);
void leituraWin(ifstream &input_file);

void printMatrix();
void twoOpt(vector<int> caminho,int carro);
void twoOpt2(vector<int> caminho,int carro, vector<int> estacoes);
float custo(vector<int> caminho);
vector<int> swap(int a, int b,vector<int> caminho);
void imprimeCaminho(vector<int> caminho, vector<int> estacoes);
void trocaBateria(float percent, float &auxBat, int &noAtual, vector<int> &estacoes, int &trocasBat, vector<int> &caminho,int proxNo);

#endif // AUXFUNC_H_INCLUDED
