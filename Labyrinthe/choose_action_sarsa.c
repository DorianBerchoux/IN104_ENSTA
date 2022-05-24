#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "choose_action_sarsa.h"

//Fichier contenant les fonctions permettant de choisir une action, modifiées pour faire fonctionner l'algorithme sarsa.


//2eme version de la fonction imaxQ qui permet de parcourir les cases de la liste Q[s] dans un ordre aléatoire 
//lors de la recherche du max, afin d'éviter de choisir toujours le premier maximum lorsque des cases ont la même valeur.
int imaxQ_sarsa (int i, int j, float** Q){

	srand(time(0));
    int s=i*(cols) + j;
    int T[4];
	for (int i=0; i<4;i++){
		T[i]=i;
	}

	int l=4;

	int rang = rand()%l;
	int indice = T[rang];


	while(l>1){

		for(int k=rang;k<3;k++){
			T[k]=T[k+1];
		}
		l=l-1;
		rang = rand()%l;
		int val=T[rang];
		if(Q[s][val]>Q[s][indice]){
			indice =val;		
		}
	}

	return indice;


    
}

//Modification de la fonction eps_greedy pour prendre en compte la nouvelle fonction imaxQ_sarsa.

action Q_eps_greedy_sarsa(float eps, float** Q){
//on choisit l'action à l'aide de la méthode eps-greedy

//on commence par choisir un nombre aléatoirement entre 0 et 1
//si le nb est plus petit ou égal à eps, on choisit une action aléatoire
    float p=randdouble();
    //p est un réel aléatoire entre 0 et 1
    if (p<=eps){
        //alors on choisit une action aléatoirement
        return env_action_sample();
    }else{
        int colmax=imaxQ_sarsa(state_row, state_col,Q);
        return colmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}