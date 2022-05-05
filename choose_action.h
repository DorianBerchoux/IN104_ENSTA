#include<stdio.h>
#include "mazeEnv.h"
#include "functions.h"

 

int imaxQ(int i, int j, float** Q);
float randdouble();
action Q_eps_greedy(float eps, float** Q);
action Q_boltzmann(float** Q);