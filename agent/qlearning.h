#ifndef QLEARNING_H
#define QLEARNING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float** makeQ();

double randdouble();

float recompense(int i, int j);

int imaxQ(int i, int j, float** Q);

action Q_eps_greedy(action a,double eps);

void actualisationQ (float alpha, float gamma, float** Q, int i, int j, action a);

void actualisation_position(action a);


