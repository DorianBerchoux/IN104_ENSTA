
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"

/*
loop for each episode : boucle de genre 400 itérations = un épisode
et on met plusieurs épisodes

ou épisode qui s'arrète quand il arrive à la fonction
et grande boucle s'arrète au bout de par exemple 4000 itérations.
*/

int main(){

maze_make("~/IN104/projet/environnement/CMaze-main/maze.txt"); //On met quel filename ?

	maze_reset(); //on part de (start_row,start_col)

	float** Q = makeQ();
	int n=0;

	for(int i=0; i<100; i++){


		while((state_row != goal_row) && (state_col!=goal_col)){

			action a = Q_eps_greedy(eps);

			float r = recompense(a); //faut modifier la fonction récompense pour qu'elle prenne que a en paramètre !!


			actualisationQ(alpha,gamma,Q,state_row,state_col,a, float r);
		

			actualisation_position(a); //actualise state_row/col
		}
		
	}
}
	

	//On part d'un état s initial (ie une position initiale)
	//On choisit une action au hasard
	//On calcule la récompense de la case s' où on se rend
	//On actualise la valeur de Q(s,a), associée à la case ou se trouve AVANT de faire l'action
	//On actualise la positon s<-s' en effectuant le déplacement q'implique l'action 
	//On continue tant que s != goal.


	//on est sur un état s, on choisit une action, on actualise Q puis on actualise la position.

