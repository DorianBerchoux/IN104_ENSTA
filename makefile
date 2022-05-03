prog: main.o functions.o mazeEnv.o qlearning.o choose_action.o dfs.o
	gcc -o -g prog main.o functions.o mazeEnv.o qlearning.o choose_action.o dfs.o -lm

main.o: main.c functions.h mazeEnv.h qlearning.h choose_action.h dfs.h
	gcc -c -Wall -Werror -Wfatal-errors main.c functions.h mazeEnv.h qlearning.h choose_action.h dfs.h -lm

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c -lm

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c -lm

qlearning.o : qlearning.c qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h -lm

choose_action.o : choose_action.c choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h -lm

dfs.o : dfs.c dfs.h mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c dfs.h mazeEnv.h -lm

clean :
	rm -f main functions.o mazeEnv.o qlearning.o choose_action.o