#include<stdio.h>
#include "mazeEnv.h"
#include "functions.h"

 

int imaxQ(int i, int j, float** Q);
int imaxQ_sarsa(int i, int j, float** Q,int** T);
float randdouble();
action Q_eps_greedy(float eps, float** Q);
action Q_eps_greedy_sarsa(float eps, float** Q, int** T);
action Q_boltzmann(float** Q);