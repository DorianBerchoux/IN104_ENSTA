#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** make_Z(int X0,int Y0);

float* f(int Tk,int* Z);

void RK2(int Tk,int** Z);

enum action{
     prey,
     predator,
     nothing,
};

action env_action_sample();

void freeZ();

float state_prey;
float state_predator;
float Tk;
float alpha;
float beta;
float delta;
float gamma;


int prey0;
int predator0;
int N;
float dt;
float h;