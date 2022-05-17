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

	int** T = malloc(24*sizeof(int*));
for(int i=0; i<24; i++){
    T[i]=malloc(sizeof(int)*4);
}

T[0][0]=1;
T[0][1]=2;
T[0][2]=3;
T[0][3]=4;

T[1][0]=1;
T[1][1]=2;
T[1][2]=4;
T[1][3]=3;

T[2][0]=1;
T[2][1]=3;
T[2][2]=4;
T[2][3]=2;

T[3][0]=1;
T[3][1]=3;
T[3][2]=2;
T[3][3]=4;

T[4][0]=1;
T[4][1]=4;
T[4][2]=2;
T[4][3]=3;

T[5][0]=1;
T[5][1]=4;
T[5][2]=3;
T[5][3]=2;

T[6][0]=2;
T[6][1]=1;
T[6][2]=3;
T[6][3]=4;

T[7][0]=2;
T[7][1]=1;
T[7][2]=4;
T[7][3]=3;

T[8][0]=2;
T[8][1]=3;
T[8][2]=1;
T[8][3]=4;

T[9][0]=2;
T[9][1]=3;
T[9][2]=4;
T[9][3]=1;

T[10][0]=2;
T[10][1]=4;
T[10][2]=1;
T[10][3]=3;

T[11][0]=2;
T[11][1]=4;
T[11][2]=3;
T[11][3]=1;

T[12][0]=3;
T[12][1]=1;
T[12][2]=2;
T[12][3]=4;

T[13][0]=3;
T[13][1]=1;
T[13][2]=4;
T[13][3]=2;

T[14][0]=3;
T[14][1]=2;
T[14][2]=1;
T[14][3]=4;

T[15][0]=3;
T[15][1]=2;
T[15][2]=4;
T[15][3]=1;

T[16][0]=3;
T[16][1]=4;
T[16][2]=1;
T[16][3]=2;

T[17][0]=3;
T[17][1]=4;
T[17][2]=2;
T[17][3]=1;

T[18][0]=4;
T[18][1]=1;
T[18][2]=2;
T[18][3]=3;

T[19][0]=4;
T[19][1]=1;
T[19][2]=3;
T[19][3]=2;

T[20][0]=4;
T[20][1]=2;
T[20][2]=1;
T[20][3]=3;

T[21][0]=4;
T[21][1]=2;
T[21][2]=3;
T[21][3]=1;

T[22][0]=4;
T[22][1]=3;
T[22][2]=1;
T[22][3]=2;

T[23][0]=4;
T[23][1]=3;
T[23][2]=2;
T[23][3]=1;

	srand(time(0));
	maze_make("maze.txt");

	float eps = 0.1;
	float alpha = 0.8;
	float gamma =0.8;

	float** Q= makeQ();

	//On loop sur les épisodes (=parcours du laby)
	for(int i=0;i<600;i++){
		maze_make("maze.txt");
		maze_reset();
		init_visited();

		int count =0;

		//On choisit une action a
		action a = Q_eps_greedy(eps,Q,T);

		printf("départ %d %d actuelle %d %d goal %d %d", state_row, state_col, state_row, state_col, goal_row, goal_col);
		
			
		

		while (((state_row != goal_row) || (state_col!=goal_col)) && (count <500)){

			
			//On calcule la récompense r associée a cette action
			float r = recompense(a);

			//On garde en mémoire la position s où on était avant de faire l'action
			int old_row = state_row;
			int old_col = state_col;

			//on actualise la postion s <- s' position après l'action
			actualisation_position(a);

			//On choisit une action a' grâce à la position s'
			action a2 = Q_eps_greedy(eps,Q,T);
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
	eps=0.1; 
	int count =0;



		//On choisit une action a
		action a = Q_eps_greedy(eps,Q,T);

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
			action a2 = Q_eps_greedy(eps,Q,T);
			
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


for(int i=0;i<24;i++){
        free(T[i]);
    }

    free(T);


}

