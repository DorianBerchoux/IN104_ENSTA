prog:  main.o qlearning.o choose_action.o lotka_volterra.o
	gcc -o prog main.o qlearning.o choose_action.o lotka_volterra.o  -lm

lotka_volterra.o : lotka_volterra.c lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors lotka_volterra.c lotka_volterra.h -lm

choose_action.o : choose_action.c choose_action.h lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h lotka_volterra.h -lm

qlearning.o : qlearning.c qlearning.h choose_action.h lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h choose_action.h lotka_volterra.h -lm

main.o : main.c qlearning.h choose_action.h lotka_volterra.h
	gcc -c -Wall -Werror -Wfatal-errors main.c qlearning.h choose_action.h lotka_volterra.h -lm	

clean :
	rm -f qlearning.o choose_action.o lotka_volterra.o main.o