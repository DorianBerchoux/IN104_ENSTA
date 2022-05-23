#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"

void doublemakeQ();
float recompense(action a );
void double_actualisationQ (float gamma, float alpha, float** Q1,float** Q2, action a, float r);
void actualisation_position(action a);


