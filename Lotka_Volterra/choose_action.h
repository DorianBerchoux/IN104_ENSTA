#ifndef CHOOSE_ACTION_H
#define CHOOSE_ACTION_H

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "lotka_volterra.h"
 

int imaxQ(int Tk, float** Q);
float randdouble();
action Q_eps_greedy(float eps, float** Q);

#endif /* CHOOSE_ACTION_H */