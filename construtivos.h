#ifndef CONSTRUTIVOS_H_INCLUDED
#define CONSTRUTIVOS_H_INCLUDED

#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

extern vector<vector<float>> distancias;
extern vector<pair<int, int>> nodeCoords;
extern vector<pair<int, int>> bssCoords;
extern vector<int> nodeDemands;
extern int nodeCount, vehicleCapacity, nodeBase, bssCost, bssCount, vehiclesNeeded, totalDemand;
extern float batteryCapacity;

void construtivoGuloso();
void construtivoGulosoRand();
void construtivoGulosoBuscaEstacao(float percent);

#endif // CONSTRUTIVOS_H_INCLUDED