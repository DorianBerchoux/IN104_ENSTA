#ifndef _DOUBLEQLEARNING_H_
#define _DOUBLEQLEARNING_H_



#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"

void doublemakeQ();

float** Q1;
float** Q2;

void doubleQ_init();

void double_actualisationQ (float gamma, float alpha, float** Q1,float** Q2, action a, float r);

#endif

