prog: main.o functions.o mazeEnv.o qlearning.o choose_action.o
	gcc -o prog main.o functions.o mazeEnv.o qlearning.o choose_action.o -lm

main.o: main.c functions.h mazeEnv.h qlearning.h choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors main.c functions.h mazeEnv.h qlearning.h choose_action.h -lm

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c -lm

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c -lm

qlearning.o : qlearning.c qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h -lm

choose_action.o : choose_action.c choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h -lm

clean :
	rm -f main functions.o mazeEnv.o qlearning.o choose_action.o