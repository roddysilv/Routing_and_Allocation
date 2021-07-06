#include "auxFunc.h"
#include "construtivos.h"
#include "script.h"

void run()
{
    vector<string> instancias=
    {
        "instances/P-n7-k3.txt",
        "instances/P-n8-k3.txt",
        "instances/P-n16-k8.txt",
        "instances/P-n19-k2.txt",
        "instances/P-n21-k2.txt",
        "instances/P-n23-k8.txt",
        "instances/P-n40-k5.txt",
        "instances/P-n45-k5.txt",
        "instances/P-n50-k7.txt",
        "instances/P-n55-k7.txt",
        "instances/P-n60-k10.txt",
        "instances/P-n70-k10.txt",
        "instances/tail75a.txt",
        "instances/tail100a.txt",
        "instances/tail150a.txt"
    };

    for(int i = 0; i < instancias.size(); i++)
    {
        cout<< instancias[i]<<endl;
        ifstream input_file(instancias[i]);
        leituraWin(input_file);
        construtivoGuloso();
    }
}
