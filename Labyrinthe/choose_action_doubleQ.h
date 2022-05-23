
#include<stdio.h>

#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"

int imaxQ_doubleQ (int i, int j, float** Q1, float** Q2);
action doubleQ_eps_greedy(float eps, float** Q1, float** Q2);