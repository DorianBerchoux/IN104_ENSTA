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
    for (int row=0;i<rows*cols;++i){
        Q[row]=malloc(sizeof(double)*4);
        //4, une colonne pour chaque action : haut,bas,gauche,droite
        if (Q[row]==NULL){
            printf("Erreur creation de la matrice Q\n");
            return NULL;
        }
        for (int col=0;j<4;++j){
            Q[row][col]=0.0;
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
    int row=state_row*cols+state_col;
    double max=Q[row][0];
    int colmax=0;
    for (int col=1;col<4;++j){
        if (Q[row][col]>res){
            max=Q[row][col];
            colmax=j;
        }
    }
    //on retourne l'indice (colonne) du max
    return colmax;
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
        int colmax=maxQ(s);
        return colmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}

action Q_blotzmann(action a){
    double sum=0.0;
    //on va stocker ici la somme des exp(Q(s,a)) pour en déduire des probabilités
    
}
