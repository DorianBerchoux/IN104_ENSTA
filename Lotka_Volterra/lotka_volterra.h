#include <stdio.h>
#include <stdlib.h>

float** make_Z(float X0,float Y0);

float* f(int Tk,float* Z);

void RK2(int Tk,float** Z);

enum action{
     prey,
     predator,
     nothing,
};

action env_action_sample();

float state_prey;
float state_predator;
float Tk;
float alpha;
float beta;
float delta;
float gamma;


float prey0;
float predator0;
int N;
float dt;
float h;