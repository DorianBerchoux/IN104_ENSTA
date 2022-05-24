#ifndef QLEARNING_H
#define QLEARNING_H

#include<stdio.h>
#include <stdlib.h>
#include <math.h>

#include "choose_action.h"


float** makeQ();

void freeQ(float** Q);

float recompense(action a);

void actualisationQ (float facteur_actualisation, float apprentissage, float** Q, action a, float r);

#endif /* QLEARNING_H */