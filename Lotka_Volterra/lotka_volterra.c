#include <stdio.h>
#include <stdlib.h>
#include "lotka_volterra.h"
//On modélise un lac, contenant des poissons : des proies et des prédateurs
float alpha=0.5; //taux reproduction proies
float beta=0.2; //taux mortalité proies
float delta=0.3; //taux reproduction prédateurs
float gamma=0.2; //taux mortalité prédateurs
//Condition initiale : X0, proies et Y0, prédateurs
float prey0=1000;
float predator0=50;

//le temps de l'expérience t varie entre 0 et 365 (en jours)
//on prendra un pas de temps dt d'une demie-journée.
float dt=0.5;
int N=365;
float h=dt/N;

float** make_Z(float prey0,float predator0){
    //On crée notre matrice Z contenant les population des espèces, première colonne les proies et deuxième colonne les prédateurs
    float** Z = malloc(sizeof(float*)*365/dt);
    if (Z!=NULL){
        for (int i=0;i<365/dt;++i){
            Z[i]=malloc(sizeof(float)*2);
            if (Z[i]!=NULL){
                if (i==0){
                    Z[i][0]=prey0;
                    Z[i][1]=predator0;
                }else{
                    Z[i][0]=0.0;
                    Z[i][1]=0.0;
                }
            }else printf("Erreur malloc");
        }
    }else printf("Erreur malloc");
}


float* f(int Tk,float* Z){
    //Définition de notre fonction f de notre système d'équations différentielles
    float res[2];
    res[0]=(alpha-beta*Z[1])*Z[0];
    res[1]=(delta*Z[0]-gamma)*Z[1];
    return res;
}

void RK2(int Tk,float** Z){
    //On utilise l'algorithme Runge-Kutta d'ordre 2 pour calculer numériquement les solutions 
    float* k1=f(Tk,Z);
    float* buffer[2];
    buffer[0]=k1[0]*h+Z[Tk][0];
    buffer[1]=k1[1]*h+Z[Tk][1];
    float* k2=f(Tk+1,buffer);
    //On calcule nos nouvelles populations
    Z[Tk+1][0]=Z[Tk][0]+(h/2)*(k1[0]+k2[0]);
    Z[Tk+1][1]=Z[Tk][1]+(h/2)*(k1[1]+k2[1]);
}


action env_action_sample(){
  return (enum action)(rand() % 3);
}







