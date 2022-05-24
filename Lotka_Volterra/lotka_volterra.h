#ifndef LOTKA_VOLTERRA_H
#define LOTKA_VOLTERRA_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float** make_Z();

float* f(int Tk,float* Z,float alpha,float beta,float gamma,float delta);

void RK2(int Tk,float** Z,float alpha,float beta,float gamma,float delta);

enum action{
     prey,
     predator,
     nothing
};

typedef enum action action ;

action env_action_sample();


void Z_reset(float** Z);
void freeZ(float** Z);

float state_prey;
float state_predator;
float Tk;

float prey0;
float predator0;
int N;
float dt;
float h;

#endif /* LOTKA_VOLTERRA_H */