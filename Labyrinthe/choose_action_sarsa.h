#include<stdio.h>

#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"


int imaxQ_sarsa(int i, int j, float** Q);
action Q_eps_greedy_sarsa(float eps, float** Q);