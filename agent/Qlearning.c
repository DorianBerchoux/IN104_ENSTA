#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Qlearning.h"
#include "mazeEnv.h"

#define alpha=0.5;
#define eps=0.3;
#define gamma=0.3;

//on crée la matrice Q
double** create_Q(){
    double** Q=malloc(sizeof(double*)*rows*cols);
    //rows*cols : nombre d'états possible
    if (Q==NULL){
        printf("Erreur creation de la matrice Q\n");
        return NULL;
    }
    for (int i=0;i<rows*cols;++i){
        Q[i]=malloc(sizeof(double)*4);
        //4, une colonne pour chaque action : haut,bas,gauche,droite
        if (Q[i]==NULL){
            printf("Erreur creation de la matrice Q\n");
            return NULL;
        }
        for (int j=0;j<4;++j){
            Q[i][j]=0.0;
        }
    }
    return Q;
}

double randdouble(){
    srand(time(NULL));
    double res=rand()/(RAND_MAX+1.0);
    return res;
}

int maxQ(){
    //on calcule l'indice de l'état state dans notre matrice Q
    int i=state_row*col+state_col;
    double max=Q[i][0];
    int jmax=0;
    for (int j=1;j<4;++j){
        if (Q[i][j]>res){
            max=Q[i][j];
            jmax=j;
        }
    }
    //on retourne l'indice (colonne) du max
    return jmax;
}


action Q_eps_greedy(action a,double eps){
//on choisit l'action à l'aide de la méthode eps-greedy

//on commence par choisir un nombre aléatoirement entre 0 et 1
//si le nb est plus petit ou égal à eps, on choisit une action aléatoire
    double p=randdouble();
    //p est un réel aléatoire entre 0 et 1
    if (p<=eps){
        //alors on choisit une action aléatoirement
        srand(time(NULL));
        int move=rand()%4;
        //on a un nombre entre 0 et 2, soit 4 valeurs possibles.
        return move;
    }else{
        int jmax=maxQ(s);
        return jmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}

action Q_blotzmann(action a){
    double sum=0.0;
    //on va stocker ici la somme des exp(Q(s,a)) pour en déduire des probabilités
    
}
