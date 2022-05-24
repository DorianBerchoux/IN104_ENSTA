
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include "lotka_volterra.h"
#include "choose_action.h"

//Rappel : eps = 0.4 , alpha =0.9, gamma=0.9

/*
loop for each episode : boucle de genre 400 itérations = un épisode
et on met plusieurs épisodes

ou épisode qui s'arrète quand il arrive à la fonction
et grande boucle s'arrète au bout de par exemple 4000 itérations.
*/

int main(){
	srand(time(0)); 
	float eps = 0.4;
	float apprentissage = 0.9;
	float gamma = 0.9;
	//on construit notre modèle
	makeZ();
	//on définit l'indice du pas de temps
	int Tk;
	//on crée notre matrice Q
	float** Q = makeQ();
	//on réalise 100 épisodes
	for(int i=0; i<100; i++){
		//on réinitialise notre liste Z
		Z_reset();
		Tk=0;
		//on boucle sur notre nombre d'itérations prédéfini s'il reste des proies et des prédateurs
		//le but étant de conserver l'écosystème
		while (Tk<(N/dt) && state_prey!=0 && state_predator!=0){
			//D'abord on choisit une action à faire
			action a = Q_eps_greedy(eps,Q);
			printf("action %d\n",a);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q et notre position
			actualisationQ(gamma,apprentissage,Q,a,r);
			//Pour finir on actualise nos populations 
			RK2(Tk,Z);
			//Enfin on incrémente notre pas de temps
			++Tk;
		}
	}
}
	

	//On part d'un état s initial (ie une position initiale)
	//On choisit une action au hasard
	//On calcule la récompense de la case s' où on se rend
	//On actualise la valeur de Q(s,a), associée à la case ou se trouve AVANT de faire l'action
	//On actualise la positon s<-s' en effectuant le déplacement q'implique l'action 
	//On continue tant que s != goal.


	//on est sur un état s, on choisit une action, on actualise Q puis on actualise la position.

