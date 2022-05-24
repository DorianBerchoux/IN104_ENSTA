#include<stdio.h>
#include<stdlib.h>
#include"qlearning.h"

//Fichier contenant les fonctions relatives à la création, libération et actualisation de la matrice Q, permettant de faire fonction l'algorithme Q-learning

//On crée la matrice Q
float** makeQ (){

	float** Q = malloc((rows)*(cols)*sizeof(float*));
	
	if (Q==NULL){
		printf("erreur allocation");
		return NULL;
	}

	for(int i=0; i<(rows)*(cols); i++){
		Q[i]=malloc(4*sizeof(float));
		if (Q[i]==NULL){
			printf("erreur allocation");
			return NULL;
		}

		else{

			for(int j=0; i<4; i++){
				Q[i][j]=0;
			}	
		}
	}

	return Q;
}

//Libération de la mémoire associée à la matrice Q.
void freeQ (float** Q){
	for(int i=0;i<(rows*cols);i++){
		free(Q[i]);
	}
	free(Q);
}

//Renvoie la récompense associée à la case où emmène l'action a.
float recompense(action a){

	

	if(a==up){
		if (maze[state_row-1][state_col] == '+'){
			return -0.1;
		}

		else if ((state_row-1==goal_row) && (state_col==goal_col)){
			return 1;	
		}
		else return -0.01;
	}

	else if(a==down){
		if(maze[state_row+1][state_col] == '+'){
			return -0.1;
		}

		else if((state_row+1==goal_row) && (state_col==goal_col)){
			return 1;
		}
		else return -0.01;
	}

	else if(a==right){
		if(maze[state_row][state_col+1] == '+'){
			return -0.1;
		}

		else if((state_row==goal_row) && (state_col+1==goal_col)){
			return 1;
		}
		else return -0.01;
	}

	else if(a==left){
		if(maze[state_row][state_col-1] == '+'){
			return -0.1;
		}

		else if((state_row==goal_row) && (state_col-1==goal_col)){
			return 1;
		}
		else return -0.01;
	}

return 0;

}

//Actualisation de la matrice Q en fonction de l'action choisie.
void actualisationQ (float gamma,float alpha, float** Q,  action a,float r){



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

//Actualisation de la position de l'agent en fonction de l'action choisie.
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


