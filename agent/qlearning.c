#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include "choose_action.h"



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

double randdouble(){
    srand(time(NULL));
    double res=rand()/(RAND_MAX+1.0);
    return res;


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
int imaxQ (int i, int j, float** Q){
	int indice=0;
	int s=i*cols + j;
	for (int k=0;k<4;k++){
		if (Q[s][k]>Q[s][indice]){
			indice=k;
		}
	}

	return indice;
}

action Q_eps_greedy(action a,double eps){
//on choisit l'action à l'aide de la méthode eps-greedy

//on commence par choisir un nombre aléatoirement entre 0 et 1
//si le nb est plus petit ou égal à eps, on choisit une action aléatoire
    double p=randdouble();
    //p est un réel aléatoire entre 0 et 1
    if (p<=eps){
        //alors on choisit une action aléatoirement
        srand(time(NULL));
        int move=rand()%4;
        //on a un nombre entre 0 et 2, soit 4 valeurs possibles.
        return move;
    }else{
        int jmax=maxQ(s);
        return jmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}

void actualisationQ (float alpha, float gamma, float** Q, int i, int j, action a){

	// i et j donnent les coordonnées de la case ou on est, ie donnent l'état actuel

	// a modif pour utiliser state row er state col.
	int s=i*cols +j;


	if (a ==up){ //up
		int r = recompense(i-1,j);
		Q[s][0] = Q[s][0] + alpha*(r +gamma*Q[(i-1)*cols +j][imaxQ(i-1,j,Q)] -Q[s][0]);

	}

	if(a ==down){//down
		int r=recompense(i+1,j);
		Q[s][1] = Q[s][1]+ alpha*(r + gamma*Q[(i+1)*cols +j][imaxQ(i+1,j,Q)] -Q[s][1]);
	}

	if(a ==left){//left
		int r=recompense(i,j-1);
		Q[s][2] = Q[s][2] +alpha*(r +gamma*Q[i*cols +j-1][imaxQ(i,j-1,Q)] -Q[s][2]);

	}

	if(a ==right){//right
		int r=recompense(i,j+1);
		Q[s][3] = Q[s][3]+alpha*(r+gamma*Q[i*cols +j+1][imaxQ(i,j+1,Q)]-Q[s][3]);

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





int main(){

	maze_make(); //On met quel filename ?

	maze_reset(); //on part de (start_row,start_col)

	float** Q = makeQ();

	while((state_row != goal_row) && (state_col!=goal_col)){

		action a = Q_eps_greedy(eps);

		float r = recompense(a); //faut modifier la fonction récompense pour qu'elle prenne que a en paramètre !!


		actualisationQ(alpha,gamma,Q,state_row,state_col,a);
		

		actualisation_position(a); //actualise state_row/col 
	}

	//On part d'un état s initial (ie une position initiale)
	//On choisit une action au hasard
	//On calcule la récompense de la case s' où on se rend
	//On actualise la valeur de Q(s,a), associée à la case ou se trouve AVANT de faire l'action
	//On actualise la positon s<-s' en effectuant le déplacement q'implique l'action 
	//On continue tant que s != goal.


	//on est sur un état s, on choisit une action, on actualise Q puis on actualise la position.






