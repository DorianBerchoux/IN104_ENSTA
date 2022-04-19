
#include "qlearning.h"
#include "mazeEnv.h"
#include "functions.h"

 
#define alpha=0.5;
#define eps=0.3;
#define gamma=0.3;

double randdouble();
action Q_eps_greedy(float** Q);
action Q_blotzmann(float** Q);