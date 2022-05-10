#include<stdio.h>
#include<stdlib.h>

#inlcude"sarsa.h"

int main (){

	srand(time(0));
	maze_make("maze.txt");

	float eps = 0.4;
	float alpha = 0.5;
	floaty gamma =1;

	float** Q= makeQ();

	//On loop sur les épisodes (=parcours du laby)
	for(int i=0;i<100;i++){
		maze_make("maze.txt");
		maze_reset();
		init_visited();

		//On choisit une action a
		action a = eps_greedy(eps,Q);

		while ((state_row != goal_row) || (state_col!=goal_col)){

			
			//On calcule la récompense r associée a cette action
			float r = recompense(a);

			//On garde en mémoire la position s où on était avant de faire l'action
			int old_row = state_row;
			int old_col = state_col;

			//on actualise la postion s <- s' position après l'action
			actualisation_position(a);

			//On choisit une action a' grâce à la position s'
			action a2 = eps_greedy(eps,Q);

			//On actualise Q
			int s = old_row*cols + old_col;
			int s2 = state_row*cols + state_col;
			Q[s][a] = Q[s][a]+alpha*[r + gamma*Q[s2][a2]-Q[s][a]];

			// s<-s' : on l' a déjà fait avec actualisation position
			// a<-a'
			a=a2;

			visited[state_row][state_col]=crumb;
		}

		add_crumbs();
		maze_render();
	}
}