#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"
#include "dfs.h"


int main (){

	srand(time(0));
	maze_make("maze.txt");

	float eps = 0.3;
	float alpha = 1;
	float gamma =1;

	float** Q= makeQ();

	//On loop sur les épisodes (=parcours du laby)
	for(int i=0;i<1000;i++){
		maze_make("maze.txt");
		maze_reset();
		init_visited();

		int count =0;

		//On choisit une action a
		action a = Q_eps_greedy(eps,Q);

		printf("départ %d %d actuelle %d %d goal %d %d", state_row, state_col, state_row, state_col, goal_row, goal_col);
		
			
		

		while (((state_row != goal_row) || (state_col!=goal_col)) && (count <10000)){

			
			//On calcule la récompense r associée a cette action
			float r = recompense(a);

			//On garde en mémoire la position s où on était avant de faire l'action
			int old_row = state_row;
			int old_col = state_col;

			//on actualise la postion s <- s' position après l'action
			actualisation_position(a);

			//On choisit une action a' grâce à la position s'
			action a2 = Q_eps_greedy(eps,Q);
			printf("départ %d %d actuelle %d %d goal %d %d \n", start_row, start_col, state_row, state_col, goal_row, goal_col);

			//On actualise Q
			int s = old_row*cols + old_col;
			int s2 = state_row*cols + state_col;
			Q[s][a] = Q[s][a]+alpha*(r + gamma*Q[s2][a2]-Q[s][a]);

			// s<-s' : on l' a déjà fait avec actualisation position
			// a<-a'
			a=a2;
			++count;
			visited[state_row][state_col]=crumb;
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
	eps=0; 
	int count =0;



		//On choisit une action a
		action a = Q_eps_greedy(eps,Q);

		printf("départ %d %d actuelle %d %d goal %d %d", state_row, state_col, state_row, state_col, goal_row, goal_col);
		
			
		

		while ((state_row != goal_row) || (state_col!=goal_col)){

			
			//On calcule la récompense r associée a cette action
			float r = recompense(a);

			//On garde en mémoire la position s où on était avant de faire l'action
			int old_row = state_row;
			int old_col = state_col;

			//on actualise la postion s <- s' position après l'action
			actualisation_position(a);

			//On choisit une action a' grâce à la position s'
			action a2 = Q_eps_greedy(eps,Q);
			
			//On actualise Q
			int s = old_row*cols + old_col;
			int s2 = state_row*cols + state_col;
			Q[s][a] = Q[s][a]+alpha*(r + gamma*Q[s2][a2]-Q[s][a]);

			// s<-s' : on l' a déjà fait avec actualisation position
			// a<-a'
			a=a2;
			++count;
			printf("départ %d %d actuelle %d %d goal %d %d \n", start_row, start_col, state_row, state_col, goal_row, goal_col);

			visited[state_row][state_col]=crumb;
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

