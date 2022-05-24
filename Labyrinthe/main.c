
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "qlearning.h"
#include "doubleQlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"
#include "choose_action_sarsa.h"
#include "choose_action_doubleQ.h"
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

	//variable qui vaut 1,2 ou 3 selon l'algorithme que l'on veut éxécuter : 
	//1 = Qlearning
	//2 = sarsa
	//3 = doubleQ
	int algo =2;

	
	int count = 0;
	


	if(algo==1){

		//création de la matrice Q
		float** Q = makeQ();

		//on réalise le parcours du labyrinthe un certain nombre de fois
		for(int i=0; i<100; i++){
			maze_make("maze.txt");
			maze_reset(); //on part de (start_row,start_col)
			//on va parcourir le labyrinthe, avec un nombre d'actions limité à 1000
			count =0;
			init_visited();

		

			while (((state_row != goal_row) || (state_col!=goal_col)) && (count<1000)){
				//D'abord on choisit une action à faire
				action a = Q_eps_greedy(eps,Q);
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
		eps=0; 
		count =0;
		while ((state_row != goal_row) || (state_col!=goal_col) ){
			//D'abord on choisit une action à faire
			action a = Q_eps_greedy(eps,Q);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q
			actualisationQ(gamma,alpha,Q,a,r);
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

		freeQ(Q);


	}

	else if (algo == 2){

		
			float** Q= makeQ();
			

			//On loop sur les épisodes (=parcours du laby)
			for(int i=0;i<300;i++){
				maze_make("maze.txt");
				maze_reset();
				init_visited();

				count =0;
			

				//On choisit une action a
				action a = Q_eps_greedy_sarsa(eps,Q);

				printf("départ %d %d actuelle %d %d goal %d %d", state_row, state_col, state_row, state_col, goal_row, goal_col);
				
			
		

				while (((state_row != goal_row) || (state_col!=goal_col)) && (count <1000)){

					
					//On calcule la récompense r associée a cette action
					float r = recompense(a);

					//On garde en mémoire la position s où on était avant de faire l'action
					int old_row = state_row;
					int old_col = state_col;

					//on actualise la postion s <- s' position après l'action
					actualisation_position(a);

					//On choisit une action a' grâce à la position s'
					action a2 = Q_eps_greedy_sarsa(eps,Q);
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
				//on part de (start_row,start_col)
				maze_make("maze.txt");
				maze_reset();
				//on crée notre matrice visited
				init_visited();

				//On l'enlève l'aléatoire pour le parcours : 
				eps=0;
				int count =0;



				//On choisit une action a
				action a = Q_eps_greedy_sarsa(eps,Q);

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
					action a2 = Q_eps_greedy_sarsa(eps,Q);
					
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

	else {

	
			
	
		//on créé les deux matrice Q1 et Q2
		
		doublemakeQ();

		printf("ok2\n");

		doubleQinit(); 


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

	
	
}



	

	//On part d'un état s initial (ie une position initiale)
	//On choisit une action au hasard
	//On calcule la récompense de la case s' où on se rend
	//On actualise la valeur de Q(s,a), associée à la case ou se trouve AVANT de faire l'action
	//On actualise la positon s<-s' en effectuant le déplacement q'implique l'action 
	//On continue tant que s != goal.


	//on est sur un état s, on choisit une action, on actualise Q puis on actualise la position.

