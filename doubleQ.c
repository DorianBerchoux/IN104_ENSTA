#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include"doubleQlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"
#include "dfs.h"



//Rappel : eps = 0.4 , alpha =0.9, gamma=0.9

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

	float eps = 0.4;
	float alpha = 0.9;
	float gamma = 0.9;
	
    printf("ok1\n");

	int count = 0;
	//on créé notre matrice Q
	
    //doublemakeQ();

	 Q1 = malloc(rows*cols*sizeof(float*));
	 Q2 = malloc(rows*cols*sizeof(float*));

	if((Q1==NULL)||(Q2==NULL)){
		printf("erreur alloc");
	}

	for(int i=0; i<rows*cols;i++){
		Q1[i]=malloc(4*sizeof(float));
		Q2[i]=malloc(4*sizeof(float));
		if((Q1[i]=NULL) || (Q2[i]=NULL)){
			printf("erreur alloc 2");
		}
	}

    printf("ok2\n");

	//doubleQ_init(); 

	printf("ok\n");
	Q1[0][0]=0;
	printf("ok3");
    for (int i=0;i<rows*cols;i++){
        for (int j=0;j<4;j++){
			printf("ok11\n");
            Q1[i][j]=0;
			printf("ok1\n");
            Q2[i][j]=0;
			printf("ok2\n");

        }
    }

	printf("ok3\n");

	//on réalise le parcours du labyrinthe 100 fois
	for(int i=0; i<100; i++){
		maze_make("maze.txt");
		maze_reset(); //on part de (start_row,start_col)
		//on va parcourir le labyrinthe, avec un nombre d'actions limité à 1000
		count =0;
		init_visited();
		while (((state_row != goal_row) || (state_col!=goal_col)) && (count<10000)){
			//D'abord on choisit une action à faire
			action a = doubleQ_eps_greedy(eps,Q1,Q2);
			printf("action %d\n",a);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q
			double_actualisationQ(gamma,alpha,Q1,Q2,a,r);
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
	eps=0; 
	count =0;
	while ((state_row != goal_row) || (state_col!=goal_col) ){
		//D'abord on choisit une action à faire
			action a = doubleQ_eps_greedy(eps,Q1,Q2);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q
			double_actualisationQ(gamma,alpha,Q1,Q2,a,r);
			//Pour finir on actualise notre position
			actualisation_position(a);
			//On actualise notre matrice visited
			visited[state_row][state_col]=crumb;
			++count;
			printf("count pour le dernier parcours %d\n",count);
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

	
    freeQ(Q1);
    freeQ(Q2);
}
	

	