#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "choose_action.h"
#include "mazeEnv.h"

struct maillon{
    struct maillon* suivant;
    int indice;
};

struct liste_chainee{
    struct maillon* debut;
    int longueur;
};

float randdouble(){
    float res=(float)(rand()%RAND_MAX)/RAND_MAX;
    return res;
}

int imaxQ (int i, int j, float** Q){
	int indice=0;
	int s=i*(cols) + j;
	for (int k=0;k<4;k++){
		if (Q[s][k]>Q[s][indice]){
			indice=k;
		}
	}
	return indice;
}

int imaxQ (int i,int j, float** Q){
    //on initialise notre liste chaînée
    struct maillon last={NULL, 3};
    struct maillon case3={&last,2};
    struct maillon case2={&case3,1};
    struct maillon first={&case2,0};
    struct liste_chainee={&first,4};

    float p = randdouble();
    if (p<0.25){
        int indice=0;
    }else if (p<0.5){
        int indice = 1;
    }else if (p<0.75){
        int indice = 2;
    }else int indice=3;
    
    //on supprime la "indice"-ième case 
    for (int i=0;i<=indice;++i){
        
    }

}




action Q_eps_greedy(float eps, float** Q){
//on choisit l'action à l'aide de la méthode eps-greedy

//on commence par choisir un nombre aléatoirement entre 0 et 1
//si le nb est plus petit ou égal à eps, on choisit une action aléatoire
    float p=randdouble();
    //p est un réel aléatoire entre 0 et 1
    if (p<=eps){
        //alors on choisit une action aléatoirement
        return env_action_sample();
    }else{
        int colmax=imaxQ(state_row, state_col,Q);
        return colmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}

action Q_boltzmann(float** Q){
    float sum=0.0;
    int row=state_row*(cols)+state_col;//on calcule la ligne correspondante à notre état s de notre matrice Q
    //on va stocker ici la somme des exp(Q(s,a)) pour en déduire les 4 différentes probabilités 
    for (int i=0;i<4;++i){
        
        sum=sum+exp(Q[row][i]);
    }
    //on calcule les probas 
    float proba[4];
    for (int i=0;i<4;++i){
        proba[i]=(float)exp(Q[row][i])/sum;
    }
    //on choisit un nombre entre 0 et 1 : s'il est entre 0 et proba[0], on choisit l'action 0 ; s'il est entre proba[0] et proba[1], on fait l'action 1 ...
    float p=randdouble();

    printf("probas %f %f %f %f\n", proba[0],proba[1],proba[2],proba[3]);
    if (0<=p && p<proba[0]){
        return up;
    }else if (proba[0]<=p && p<proba[1]+proba[0]){
        return down;
    }else if (proba[1]+proba[0]<=p && p<proba[2]+proba[1]+proba[0]){
        return left;
    }else if(proba[2]+proba[1]+proba[0]<=p  && p<=1){
        return right;
    }else return 1;
}

