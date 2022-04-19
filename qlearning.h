





#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"

float** makeQ();



float recompense(action a );

int imaxQ(float** Q);


void actualisationQ (float alpha, float gamma, float** Q, int i, int j, action a, float r);

void actualisation_position(action a);


