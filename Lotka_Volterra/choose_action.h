#include<stdio.h>
#include "mazeEnv.h"
#include "functions.h"

 

int imaxQ(int i, int j, float** Q);
int imaxQ_sarsa(int i, int j, float** Q,int** T);
int imaxQ_doubleQ (int i, int j, float** Q1, float** Q2);
float randdouble();
action Q_eps_greedy(float eps, float** Q);
action Q_eps_greedy_sarsa(float eps, float** Q, int** T);
action doubleQ_eps_greedy(float eps, float** Q1, float** Q2);
action Q_boltzmann(float** Q);