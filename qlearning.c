#include<stdio.h>
#include<stdlib.h>

#include"qlearning.h"



//On crée la matrice Q
float** makeQ (){

	float** Q = malloc(rows*cols*sizeof(float*));
	
	if (Q==NULL){
		printf("erreur allocation");
		return NULL;
	}

	for(int i=0; i<rows*cols; i++){
		Q[i]=malloc(4*sizeof(float));
		if (Q[i]==NULL){
			printf("erreur allocation");
			return NULL;
		}

		for(int j=0; i<4; i++){
			Q[i][j]=0;
		}	
}



//Modifier recompense pour qu'il utilise (i actuel, j actuel et l'action a choisie) ou alors state_row, state_col et l'action
//FAUT COMPRENDRE COMMENT MARCHE DFS !!!!


// }
// renvoie la recompense de la case ou on se rend



//problème : faut d'abord actualiser la position ou on se rend pour utiliser dfs car dfs utilise state row et state col
//ATTENTION : COMPRENDRE COMMENT MARCHE DFS

//recompense : 1 s'il arrive au bout, pénalité de -0,5 s'il se tape un mur et 0 sinon.






float recompense(action a){

	float r;

	if(a==up){
		if (maze[state_row-1][state_col] == '+'){
			r=-0.5;
		}

		else if ((state_row-1==goal_row) && (state_col==goal_col)){
			r=1;	
		}
	}

	else if(a==down){
		if(maze[state_row+1][state_col] == '+'){
			r=-0.5;
		}

		else if((state_row+1==goal_row) && (state_col==goal_col)){
			r=1;
		}
	}

	else if(a==right){
		if(maze[state_row][state_col+1] == '+'){
			r=-0.5;
		}

		else if((state_row==goal_row) && (state_col+1==goal_col)){
			r=1;
		}
	}

	else if(a==left){
		if(maze[state_row][state_col-1] == '+'){
			r=-0.5;
		}

		else if((state_row==goal_row) && (state_col-1==goal_col)){
			r=1;
		}
	}


}



//calcule de l'indice de maxQ(s',a)
int imaxQ (float** Q){
	int indice=0;
	int s=state_row*cols + state_col;
	for (int k=0;k<4;k++){
		if (Q[s][k]>Q[s][indice]){
			indice=k;
		}
	}

	return indice;
}



void actualisationQ (float alpha, float gamma, float** Q, int i, int j, action a,float r){

	// i et j donnent les coordonnées de la case ou on est, ie donnent l'état actuel

	// a modif pour utiliser state row er state col.
	

	int s = state_row*cols + state_col;


	if (a ==up){ //up
	
		Q[s][0] = Q[s][0] + alpha*(r +gamma*Q[(state_row-1)*cols +state_col][imaxQ(state_row-1,state_col,Q)] -Q[s][0]);

	}

	if(a ==down){//down
		
		Q[s][1] = Q[s][1]+ alpha*(r + gamma*Q[(state_row+1)*cols +j][imaxQ(state_row+1,state_col,Q)] -Q[s][1]);
	}

	if(a ==left){//left
		
		Q[s][2] = Q[s][2] +alpha*(r +gamma*Q[state_row*cols +state_col-1][imaxQ(state_row,state_col-1,Q)] -Q[s][2]);

	}

	if(a ==right){//right
		
		Q[s][3] = Q[s][3]+alpha*(r+gamma*Q[state_row*cols +state_col+1][imaxQ(state_row,state_col+1,Q)]-Q[s][3]);

	}

}



void actualisation_position(action a){

	if(a==up){
		if (maze[state_row-1][state_col] != '+'){
			state_row =state_row-1;		
		}
	}

	else if(a==down){
		if(maze[state_row,+1][state_col] != '+'){
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

