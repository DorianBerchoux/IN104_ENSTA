#ifndef QLEARNING_H
#define QLEARNING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float** makeQ();



float recompense(action a );

int imaxQ(float** Q);


void actualisationQ (float alpha, float gamma, float** Q, int i, int j, action a, float r);

void actualisation_position(action a);


