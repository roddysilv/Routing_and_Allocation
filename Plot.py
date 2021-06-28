# -*- coding: utf-8 -*-
"""
Created on Thu Jun 24 19:09:08 2021

@author: Rodrigo
"""

import pandas as pd
import matplotlib.pyplot as plt
from glob import glob


k=1
for rota in glob("Arquivos/coordenadas*.csv"):
    coord = pd.read_csv(rota)

    x = coord['x'].values
    y = coord['y'].values
    no = coord['no'].values
    
    # plt.figure()
    plt.plot(x,y,'o--',label='Veículo ' + str(k))
    plt.legend(prop={'size': 6})
    plt.xlabel("x")
    plt.ylabel("y")
    for i in range(len(no)):
        plt.annotate(no[i],(x[i],y[i]))
    k+=1