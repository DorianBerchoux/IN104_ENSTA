#include<stdio.h>
#include<stdlib.h>

#include"qlearning.h"
#include "lotka_volterra.h"
#include "choose_action.h"


//On crée la matrice Q
float** makeQ (){
	//un état : un nombre de prédateurs et un nombre de proies
	//ce nombre varie entre 0 et le nb initial*10
	//d'où la taille de notre matrice Q
	float** Q = malloc((prey0*predator0*100)*sizeof(float*));
	
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
	for(int i=0;i<(prey0*predator0*100);i++){
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
		return (state_prey/(state_prey+state_predator))*r0prey - (prey0/state_prey -1)*r0prey;
	}else if (a==1){
		//On choisit de pecher un predateur
		return (state_predator/(state_prey+state_predator))*r0predator - (predator0/state_predator -1)*r0predator;
	}else{
		return -0.1;
	}
}



//calcule de l'indice de maxQ(s',a)




void actualisationQ (float gamma,float apprentissage, float** Q,  action a,float r){
	//calcul de l'état actuel
	int s=(state_prey)*(predator0*10) + state_predator;
	//on va calculer l'état prédit s' après avoir fait l'action a
	int new_prey=state_prey;
	int new_predator=state_predator;
	if (a==0){
		//on pêche une proie
		--new_prey;
	}else if (a==1){
		//on pêche un prédateur
		--new_predator;
	}
	//on calcule notre état s' que l'on notera s2
	int s2=(new_prey)*(predator0*10)+new_predator;
	//on actualise notre matrice Q
	Q[s][a] = Q[s][a] + apprentissage*(r +gamma*Q[s2][imaxQ(Tk,Q)] -Q[s][a]);
	//après cela on actualise notre état : s -> s2
	state_prey=new_prey;
	state_predator=new_predator;
}


