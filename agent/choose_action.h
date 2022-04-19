#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Qlearning.h"
#include "mazeEnv.h"
 
#define alpha=0.5;
#define eps=0.3;
#define gamma=0.3;

double randdouble();
action Q_eps_greedy(float** Q);
action Q_blotzmann(float** Q);