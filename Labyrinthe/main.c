
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


/*
loop for each episode : boucle de genre 400 itérations = un épisode
et on met plusieurs épisodes

ou épisode qui s'arrète quand il arrive à la fonction
et grande boucle s'arrète au bout de par exemple 4000 itérations.
*/

//Main qui contient les 3 algorithmes Q-learning, sarsa et doubleQ. On modifie la valeur d'une variable "algo" selon l'algorithme que l'on veut éxécuter.

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
	
	//Algorithme Q-learning:
	if(algo==1){

		//création de la matrice Q
		float** Q = makeQ();

		//on réalise le parcours du labyrinthe un certain nombre de fois.
		for(int i=0; i<100; i++){
			maze_make("maze.txt");
			maze_reset(); //on part de (start_row,start_col)
			//on initialise à 0 un compteur d'itérations avant de commencer à parcourir un labyrinthe.
			count =0;
			init_visited();

			//On parcourir le labyrinthe tant que l'on est pas arrivé au bout et tant que l'on a pas dépassé un nombre maximal d'itérations.
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

		//Une fois l'apprentissage terminé, on effectue un dernier parcours de labyrinthe pour voir s'il arrive au bout.
		//Si le parcours est le plus court chemin, alors notre apprentissage fonctionne.

		 //on part de (start_row,start_col)
		maze_make("maze.txt");
		maze_reset();
		//on crée notre matrice visited
		init_visited();

		//On l'enlève l'aléatoire en mettant epsilon=0, afin que l'agent se base uniquement sur son apprentissage.
		eps=0; 
		count =0;
		//On continue tant que l'agent n'arrive pas au bout du labyrinthe.
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

	//algorithme sarsa
	else if (algo == 2){

		
			float** Q= makeQ();
			

			//On loop sur les épisodes 
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

					// s<-s' : on l' a déjà fait avec l'appel à actualisation position
					// a<-a'
					a=a2;
					++count;
					visited[state_row][state_col]=crumb;
				}

				add_crumbs();
				maze_render();

			}



			//Une fois l'apprentissage terminé, on effectue un dernier parcours de labyrinthe pour voir s'il arrive au bout.
			
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


			freeQ(Q);

	}

	//Algorithme double-Q
	else {

		//on crée les deux matrice Q1 et Q2
		doublemakeQ();

		//On initialise chaque case des deux matrices Q1 et Q2 à 0.
		doubleQinit(); 

		//on réalise le parcours du labyrinthe un certain nombre de fois.
		for(int i=0; i<100; i++){
			maze_make("maze.txt");
			maze_reset(); //on part de (start_row,start_col)

			//on initialise à 0 un compteur d'iérations avant chaque parcours de labyrinthe.
			count =0;
			init_visited();
			while (((state_row != goal_row) || (state_col!=goal_col)) && (count<10000)){
				//D'abord on choisit une action à faire
				action a = doubleQ_eps_greedy(eps,Q1,Q2);
				printf("action %d\n",a);
				//Puis on calcule la récompense associée à cette action
				float r = recompense(a);
				//Après on actualise nos deux matrices Q1 et Q2.
				double_actualisationQ(gamma,alpha,Q1,Q2,a,r);
				//Pour finir on actualise notre position
				actualisation_position(a); 
				visited[state_row][state_col]=crumb;
				++count;
			}
			add_crumbs();
			maze_render();
		}

		//Une fois l'apprentissage terminé, on effectue un dernier parcours de labyrinthe pour voir s'il arrive au bout.
		
		maze_make("maze.txt");
		maze_reset();
		//on crée notre matrice visited
		init_visited();

		//On l'enlève l'aléatoire pour le parcours
		eps=0; 
		count =0;
		while ((state_row != goal_row) || (state_col!=goal_col) ){
			//D'abord on choisit une action à faire
				action a = doubleQ_eps_greedy(eps,Q1,Q2);
				//Puis on calcule la récompense associée à cette action
				float r = recompense(a);
				//Après on actualise nos matrices Q1 et Q2.
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

		//On libère la mémoire.
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

