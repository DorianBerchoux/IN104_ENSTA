

#include "choose_action.h"


double randdouble(){
    srand(time(NULL));
    double res=rand()/(RAND_MAX+1.0);
    return res;
}





action Q_eps_greedy(float** Q){
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
        int colmax=imaxQ(Q);
        return colmax;
        //on choisit l'action qui va maximiser notre récompense
    }
}

action Q_blotzmann(float** Q){
    double sum=0.0;
    //on va stocker ici la somme des exp(Q(s,a)) pour en déduire les 4 différentes probabilités 
    for (int i=0;i<4;++i){
        int row=state_row*cols+state_col;//on calcule la ligne correspondante à notre état s de notre matrice Q
        sum=sum+exp(Q[row][i]);
    }
    //on calcule les probas 
    double* proba[4];
    for (int i=0;i<4;++i){
        proba[i]=exp(Q[row][i]/sum);
    }
    //on choisit un nombre entre 0 et 1 : s'il est entre 0 et proba[0], on choisit l'action 0 ; s'il est entre proba[0] et proba[1], on fait l'action 1 ...
    double p=randdouble();
    if (p<proba[0]){
        return up;
    }else if (p<proba[1]+proba[0]){
        return down;
    }else if (p<proba[2]+proba[1]+proba[0]){
        return left;
    }else{ 
        return right;
    }
}

