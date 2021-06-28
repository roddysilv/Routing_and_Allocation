#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

extern vector<vector<float>> distancias;
extern vector<pair<int, int>> nodeCoords;
extern vector<pair<int, int>> bssCoords;
extern vector<int> nodeDemands;
extern int nodeCount, vehicleCapacity, nodeBase, bssCost, bssCount, vehiclesNeeded, totalDemand;
extern float batteryCapacity;

float distance(int x1, int y1, int x2, int y2);
void saveFile(int carro, vector<int> caminho, string algoritmo);
void leitura(ifstream &input_file);
void leituraWin(ifstream &input_file);
void construtivoGuloso();
void construtivoGulosoRand();
void print();
void twoOpt(vector<int> caminho,int carro);
float custo(vector<int> caminho);
vector<int> swap(int a, int b,vector<int> caminho);

#endif // FUNCTIONS_H_INCLUDED
