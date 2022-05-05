#include<stdio.h>
#include<stdlib.h>

#include"qlearning.h"



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



//Modifier recompense pour qu'il utilise (i actuel, j actuel et l'action a choisie) ou alors state_row, state_col et l'action
//FAUT COMPRENDRE COMMENT MARCHE DFS !!!!


// }
// renvoie la recompense de la case ou on se rend



//problème : faut d'abord actualiser la position ou on se rend pour utiliser dfs car dfs utilise state row et state col
//ATTENTION : COMPRENDRE COMMENT MARCHE DFS

//recompense : 1 s'il arrive au bout, pénalité de -0,5 s'il se tape un mur et 0 sinon.






float recompense(action a){

	

	if(a==up){
		if (maze[state_row-1][state_col] == '+'){
			return -1;
		}

		else if ((state_row-1==goal_row) && (state_col==goal_col)){
			return 10;	
		}
		else return -0.5;
	}

	else if(a==down){
		if(maze[state_row+1][state_col] == '+'){
			return -1;
		}

		else if((state_row+1==goal_row) && (state_col==goal_col)){
			return 10;
		}
		else return -0.5;
	}

	else if(a==right){
		if(maze[state_row][state_col+1] == '+'){
			return -1;
		}

		else if((state_row==goal_row) && (state_col+1==goal_col)){
			return 10;
		}
		else return -0.5;
	}

	else if(a==left){
		if(maze[state_row][state_col-1] == '+'){
			return -1;
		}

		else if((state_row==goal_row) && (state_col-1==goal_col)){
			return 10;
		}
		else return -0.5;
	}

return 0;

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


