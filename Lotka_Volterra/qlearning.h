

#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"

float** makeQ();

void freeQ(float** Q);

float recompense(action a );




void actualisationQ (float gamma, float apprentissage, float** Q, action a, float r);

void double_actualisationQ (float gamma, float apprentissage, float** Q1,float** Q2, action a, float r);



void actualisation_position(action a);


