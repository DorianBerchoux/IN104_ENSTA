#include<stdio.h>
#include "mazeEnv.h"
#include "functions.h"

 

int imaxQ(int i, int j, float** Q);
double randdouble();
action Q_eps_greedy(float eps, float** Q);
action Q_blotzmann(float** Q);