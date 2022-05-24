#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"
#include "qlearning.h"

void doublemakeQ();

float** Q1;
float** Q2;
void doubleQinit();


void double_actualisationQ(float gamma, float alpha, float** Q1, float** Q2, action a, float r);
