# -*- coding: utf-8 -*-
"""
Created on Thu Jun 24 19:09:08 2021

@author: Rodrigo
"""

import pandas as pd
import matplotlib.pyplot as plt
from glob import glob


k=0
for i in range(1,12):
    # coord = pd.read_csv("Arquivos/coordenadasGuloso_"+str(i)+".csv")
    # coord = pd.read_csv("Arquivos/coordenadasGulosoRand_"+str(i)+".csv")
    # coord = pd.read_csv("Arquivos/coordenadas2opt_"+str(i)+".csv")
    # coord = pd.read_csv("Arquivos/coordenadasOptGulosoBusca_"+str(i)+".csv")
    coord = pd.read_csv("Arquivos/coordenadasGulosoBusca_"+str(i)+".csv")
    try:
        coordOpt = pd.read_csv("Arquivos/coordenadas2opt_"+str(i)+".csv")
        xOpt = coordOpt['x'].values
        yOpt = coordOpt['y'].values
        noOpt = coordOpt['no'].values
        t = 1
    except:
        t = 1    
    x = coord['x'].values
    y = coord['y'].values
    no = coord['no'].values
    estacao = coord['estacao'].values
    
    
    
    # plt.figure()
    plt.plot(x,y,'o--',label='Veículo ' + str(i))
    plt.legend(prop={'size': 6})
    plt.xlabel("x")
    plt.ylabel("y")
    for j in range(len(no)):
        if estacao[j] == 1:
            plt.annotate(no[j],(x[j],y[j]),color='r')
        else:
            plt.annotate(no[j],(x[j],y[j]))
    if (t == 0): 
        # plt.figure()
        plt.plot(xOpt,yOpt,'bo--',label='VeículoOpt ' + str(i))
        plt.legend(prop={'size': 6})
        plt.xlabel("x")
        plt.ylabel("y")
        for k in range(len(noOpt)):
            plt.annotate(noOpt[k],(xOpt[k],yOpt[k]),color='b')
