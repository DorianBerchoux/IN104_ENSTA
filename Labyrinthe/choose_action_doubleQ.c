#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "choose_action_doubleQ.h"

int imaxQ_doubleQ (int i, int j, float** Q1, float** Q2){

    int indice =0;
    int s=i*cols +j;

    //On crée une liste correspondant à la somme de Q1[s] et Q2[s]
    float QS[4];
    for (int k=0;k<4;k++){
        QS[k]=Q1[s][k]+Q2[s][k];
    }

    for (int i=0;i<4;i++){
        if(QS[i]>QS[indice]){
            indice=i;
        }
    }
    return indice;
}

action doubleQ_eps_greedy(float eps, float** Q1, float** Q2){
//on choisit l'action à l'aide de la méthode eps-greedy

//on commence par choisir un nombre aléatoirement entre 0 et 1
//si le nb est plus petit ou égal à eps, on choisit une action aléatoire
    float p=randdouble();
    //p est un réel aléatoire entre 0 et 1
    if (p<=eps){
        //alors on choisit une action aléatoirement
        return env_action_sample();
    }else{
        int colmax=imaxQ_doubleQ(state_row, state_col,Q1,Q2);
        return colmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}
