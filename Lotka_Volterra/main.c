
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include"qlearning.h"
#include "lotka_volterra.h"
#include "choose_action.h"

//Rappel : eps = 0.4 , apprentissage =0.9, facteur_actualisation=0.9

/*
loop for each episode : boucle de genre 400 itérations = un épisode
et on met plusieurs épisodes

ou épisode qui s'arrète quand il arrive à la fonction
et grande boucle s'arrète au bout de par exemple 4000 itérations.
*/

//On modélise un lac, contenant des poissons : des proies et des prédateurs
float alpha=0.5; //taux reproduction proies
float beta=0.2; //taux mortalité proies
float delta=0.3; //taux reproduction prédateurs
float gama=0.2; //taux mortalité prédateurs

//Condition initiale : X0, proies et Y0, prédateurs
float prey0=1000;
float predator0=50;

//le temps de l'expérience t varie entre 0 et 365 (en jours)
//on prendra un pas de temps dt d'une demie-journée.
//on définit alors le pas numérique h comme ci-dessous
float dt=0.5;
int N=365;
float h=1/730;

int main(){
	srand(time(0)); 
	float eps = 0.4;
	float apprentissage = 0.9;
	float facteur_actualisation = 0.9;
	//on construit notre modèle
	float** Z=make_Z();
	//on définit l'indice du pas de temps
	int Tk;
	//on crée notre matrice Q
	float** Q = makeQ();
	//on crée un compteur de récompense
	float tot_r;
	//on réalise 100 épisodes d'entraînement
	for(int i=0; i<100; i++){
		//on réinitialise notre liste Z et le temps
		Z_reset(Z);
		Tk=0;
		//on réinitialise notre récompense totale
		tot_r=0.0;
		//on boucle sur notre nombre d'itérations prédéfini N/dt, s'il reste des proies et des prédateurs
		//le but étant de conserver l'écosystème
		while (Tk<(N/dt) && state_prey!=0 && state_predator!=0){
			//D'abord on choisit une action à faire
			action a = Q_eps_greedy(eps,Q);
			printf("action %d\n",a);
			//Puis on calcule la récompense associée à cette action
			float r = recompense(a);
			//Après on actualise notre matrice Q et notre position
			actualisationQ(facteur_actualisation,apprentissage,Q,a,r);
			//Puis on actualise nos populations en fonction des populations précédentes et de l'action qu'on a prise
			RK2(Tk,Z,alpha,beta,gama,delta);
			//On actualise notre récompense totale
			tot_r=tot_r+r;
			//Enfin on incrémente notre pas de temps
			++Tk;
		}
	}
	free(Z);
}
	

	//On part d'un état s initial (ie une position initiale)
	//On choisit une action au hasard
	//On calcule la récompense de la case s' où on se rend
	//On actualise la valeur de Q(s,a), associée à la case ou se trouve AVANT de faire l'action
	//On actualise la positon s<-s' en effectuant le déplacement q'implique l'action 
	//On continue tant que s != goal.


	//on est sur un état s, on choisit une action, on actualise Q puis on actualise la position.

