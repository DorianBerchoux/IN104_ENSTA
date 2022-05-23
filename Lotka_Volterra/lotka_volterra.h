#include <stdio.h>
#include <stdlib.h>

float** make_Z(float X0,float Y0);

float* f(int Tk,float* Z);

void RK2(int Tk,float** Z);