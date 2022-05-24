#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "choose_action.h"
#include "lotka_volterra.h"



// Fonction qui permet de générer un nombre aléatoire entre 0 et 1.
float randdouble(){
    float res=(float)(rand()%RAND_MAX)/RAND_MAX;
    return res;
}

int imaxQ (int Tk,float** Q){
    //On calcule la valeur max de Q dans la ligne d'indice Tk
	int indice=0;
	for (int k=0;k<3;k++){
		if (Q[Tk][k]>Q[Tk][indice]){
			indice=k;
		}
	}
	return indice;
}

//2eme version de la fonction imaxQ qui prend en argument la matrice T qui permet de parcourir les cases de la matrice Q dans un ordre aléatoire 
//lors de la recherche du max, afin d'éviter de choisir toujours le premier maximum lorsque des cases ont la même valeur.
 
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
        int colmax=imaxQ(Tk,Q);
        return colmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}



