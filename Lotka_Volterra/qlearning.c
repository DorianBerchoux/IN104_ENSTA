#include<stdio.h>
#include<stdlib.h>

#include"qlearning.h"
#include "lotka_volterra.h"



//On crée la matrice Q
float** makeQ (){

	float** Q = malloc((N/dt)*sizeof(float*));
	
	if (Q==NULL){
		printf("erreur allocation");
		return NULL;
	}

	for(int i=0; i<(N/dt); i++){
		Q[i]=malloc(3*sizeof(float));
		if (Q[i]==NULL){
			printf("erreur allocation");
			return NULL;
		}

		else{

			for(int j=0; i<3; i++){
				Q[i][j]=0;
			}	
		}
	}

	return Q;
}

void freeQ (float** Q){
	for(int i=0;i<(N/dt);i++){
		free(Q[i]);
	}
	free(Q);
}

//Modifier recompense pour qu'il utilise (i actuel, j actuel et l'action a choisie) ou alors state_row, state_col et l'action
//FAUT COMPRENDRE COMMENT MARCHE DFS !!!!


// }
// renvoie la recompense de la case ou on se rend



//problème : faut d'abord actualiser la position ou on se rend pour utiliser dfs car dfs utilise state row et state col
//ATTENTION : COMPRENDRE COMMENT MARCHE DFS

//recompense : 1 s'il arrive au bout, pénalité de -0,5 s'il se tape un mur et 0 sinon.






float recompense(action a){
	float r0predator=9.0;
	float r0prey=3.0;
	//Ce sont des récompenses caractéristiques 
	if (a==0){
		//On choisit de pecher une proie
		//La récompense dépend du nombre de proies par rapport au début
		//Et dépend de la proportion de proies
		return (state_prey/(state_prey+state_predator) + 1)*r0prey - (prey0/state_prey -1)*r0prey;
	}else if (a==1){
		//On choisit de pecher un predateur
		return (state_predator/(state_prey+state_predator) + 1)*r0predator - (predator0/state_predator -1)*r0predator;
	}else{
		return -0.1;
	}
}



//calcule de l'indice de maxQ(s',a)




void actualisationQ (float gamma,float alpha, float** Q,  action a,float r){

	// i et j donnent les coordonnées de la case ou on est, ie donnent l'état actuel

	// a modif pour utiliser state row er state col.
	

	int s = state_row*(cols) + state_col;
	int new_col = state_col;
	int new_row = state_row;


	if(a==up){
		if (maze[state_row-1][state_col] != '+'){
			--new_row;
		}

	}

	else if(a==down){
		if(maze[state_row+1][state_col] != '+'){
			++new_row;
		}

	}

	else if(a==right){
		if(maze[state_row][state_col+1] != '+'){
			++new_col;
		}
	}

	else if(a==left){
		if(maze[state_row][state_col-1] != '+'){
			--new_col;
		}

		
	}

	



	Q[s][a] = Q[s][a] + alpha*(r +gamma*Q[(new_row)*(cols) +new_col][imaxQ(new_row,new_col,Q)] -Q[s][a]);


}

void double_actualisationQ(float gamma,float alpha, float** Q1,float** Q2 , action a,float r){

	int s = state_row*(cols) + state_col;
	int new_col = state_col;
	int new_row = state_row;


	if(a==up){
		if (maze[state_row-1][state_col] != '+'){
			--new_row;
		}

	}

	else if(a==down){
		if(maze[state_row+1][state_col] != '+'){
			++new_row;
		}

	}

	else if(a==right){
		if(maze[state_row][state_col+1] != '+'){
			++new_col;
		}
	}

	else if(a==left){
		if(maze[state_row][state_col-1] != '+'){
			--new_col;
		}

		
	}

float p=randdouble();
	if (p<=0.5){
		
		Q1[s][a] = Q1[s][a] + alpha*(r +gamma*Q2[(new_row)*(cols) +new_col][imaxQ(new_row,new_col,Q1)] -Q1[s][a]);
	}

	else{
		Q2[s][a] = Q2[s][a] + alpha*(r +gamma*Q1[(new_row)*(cols) +new_col][imaxQ(new_row,new_col,Q2)] -Q2[s][a]);
	}



}



void actualisation_position(action a){

	if(a==up){
		if (maze[state_row-1][state_col] != '+'){
			state_row =state_row-1;		
		}
	}

	else if(a==down){
		if(maze[state_row+1][state_col] != '+'){
			state_row = state_row+1;
		}
	}

	else if(a==right){
		if(maze[state_row][state_col+1] != '+'){
			state_col = state_col +1;
		}
	}

	else if(a==left){
		if(maze[state_row][state_col-1] != '+'){
			state_col = state_col -1;
		}
	}
}

