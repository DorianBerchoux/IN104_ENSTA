#include<stdio.h>
#include<stdlib.h>

#include "doubleQlearning.h"

void doublemakeQ(){

    float** Q1= malloc(rows*cols*sizeof(float*));
    float** Q2= malloc(rows*cols*sizeof(float*));

    if ((Q1==NULL) || (Q2==NULL)){
        printf("erreur alloc");
    }

    for (int i=0;i<rows*cols;i++){
        Q1[i]=malloc(4*sizeof(float));
        Q2[i]=malloc(4*sizeof(float));
        if((Q1[i]==NULL) || (Q2[i]==NULL)){
            printf("erreur alloc 2");
        }
    }
}

void doubleQinit(){

    for (int i=0;i<rows*cols;i++){
        for (int j=0;j<4;j++){
            Q1[i][j]=0;
            Q2[i][j]=0;
        }
    }
}

void double_actualisationQ(float gamma, float alpha, float** Q1, float** Q2, action a, float r){

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
    if(p<=0.5){
        Q1[s][a] = Q1[s][a] + alpha*(r +gamma*Q2[(new_row)*(cols) +new_col][imaxQ(new_row,new_col,Q1)] -Q1[s][a]);
    }
    else{
        Q2[s][a] = Q2[s][a] + alpha*(r +gamma*Q1[(new_row)*(cols) +new_col][imaxQ(new_row,new_col,Q2)] -Q2[s][a]);


    }
}