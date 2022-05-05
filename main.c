
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"
#include "dfs.h"



/*
loop for each episode : boucle de genre 400 itérations = un épisode
et on met plusieurs épisodes

ou épisode qui s'arrète quand il arrive à la fonction
et grande boucle s'arrète au bout de par exemple 4000 itérations.
*/

int main(){
	srand(time(0)); 
	//on construit notre labyrinthe
	maze_make("maze.txt"); 

	//float eps = 0.4;
	float alpha = 0.5;
	float gamma = 1;
	
	int count = 0;
	//on créé notre matrice Q
	float** Q = makeQ();
	//on réalise le parcours du labyrinthe 100 fois
	for(int i=0; i<100; i++){
		maze_make("maze.txt");
		maze_reset(); //on part de (start_row,start_col)
		//on va parcourir le labyrinthe, avec un nombre d'actions limité à 1000
		count =0;
		init_visited();
		while (((state_row != goal_row) || (state_col!=goal_col)) && (count<1000)){
			//D'abord on choisit une action à faire
			action a = Q_boltzmann(Q);
			printf("action %d\n",a);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q
			actualisationQ(gamma,alpha,Q,a,r);
			//Pour finir on actualise notre position
			actualisation_position(a); 
			visited[state_row][state_col]=crumb;
			++count;
		}
		add_crumbs();
		maze_render();
	}
	//Après avoir fait 100 parcours de labyrinthe, on regarde le parcours que l'on fait après apprentissage.
	//Si le parcours est le plus court chemin, alors notre apprentissage fonctionne.
	//On pourra ensuite chercher à optimiser cet apprentissage ou à en élaborer d'autres.
	 //on part de (start_row,start_col)
	maze_make("maze.txt");
	maze_reset();
	//on crée notre matrice visited
	init_visited();

	//On l'enlève l'aléatoire pour le parcours : il termine en 45 itérations(ie plus court chemin).
	//eps=0; 
	count =0;
	while ((state_row != goal_row) || (state_col!=goal_col) ){
		//D'abord on choisit une action à faire
			action a = Q_boltzmann(Q);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q
			actualisationQ(gamma,alpha,Q,a,r);
			//Pour finir on actualise notre position
			actualisation_position(a);
			//On actualise notre matrice visited
			visited[state_row][state_col]=crumb;
			++count;
	}
	//On modifie notre labyrinthe pour voir notre chemin
	add_crumbs();
	printf("Le chemin qu'on a parcouru\n");
	maze_render();
	printf("nb d'itérations final %d\n", count);
	//Maintenant on affiche le chemin le plus court
	printf("Le chemin le plus court\n");
	maze_make("maze.txt");
	maze_reset();
	init_visited();
	dfs(start_row,start_col);
    add_crumbs();
    maze_render();
}
	

	//On part d'un état s initial (ie une position initiale)
	//On choisit une action au hasard
	//On calcule la récompense de la case s' où on se rend
	//On actualise la valeur de Q(s,a), associée à la case ou se trouve AVANT de faire l'action
	//On actualise la positon s<-s' en effectuant le déplacement q'implique l'action 
	//On continue tant que s != goal.


	//on est sur un état s, on choisit une action, on actualise Q puis on actualise la position.

