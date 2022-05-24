<<<<<<< HEAD
prog:  main.o qlearning.o choose_action.o lotka_volterra.o
	gcc -o prog main.o qlearning.o choose_action.o lotka_volterra.o  -lm

lotka_volterra.o : lotka_volterra.c lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors lotka_volterra.c lotka_volterra.h -lm
=======
prog: doubleQ.o functions.o mazeEnv.o qlearning.o choose_action.o dfs.o 
	gcc -o prog doubleQ.o functions.o mazeEnv.o qlearning.o choose_action.o dfs.o  -lm

doubleQ.o: doubleQ.c functions.h mazeEnv.h qlearning.h choose_action.h dfs.h 
	gcc -c -Wall -Werror -Wfatal-errors doubleQ.c functions.h mazeEnv.h qlearning.h choose_action.h dfs.h  -lm
>>>>>>> 3d2387c8eeed10103ac35161dfde9a43ce771bd0

choose_action.o : choose_action.c choose_action.h lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h lotka_volterra.h -lm

qlearning.o : qlearning.c qlearning.h choose_action.h lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h choose_action.h lotka_volterra.h -lm

main.o : main.c qlearning.h choose_action.h lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors main.c qlearning.h choose_action.h lotka_volterra.h -lm	



clean :
<<<<<<< HEAD
	rm -f qlearning.o choose_action.o lotka_volterra.o main.o
=======
	rm -f doubleQ.o functions.o mazeEnv.o qlearning.o choose_action.o dfs.o 
>>>>>>> 3d2387c8eeed10103ac35161dfde9a43ce771bd0
