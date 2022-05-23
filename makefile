prog: doubleQ.o functions.o mazeEnv.o qlearning.o choose_action.o doubleQlearning.o dfs.o
	gcc -o prog doubleQ.o functions.o mazeEnv.o qlearning.o choose_action.o doubleQlearning.o dfs.o -lm

doubleQ.o: doubleQ.c functions.h mazeEnv.h qlearning.h choose_action.h doubleQlearning.h dfs.h
	gcc -c -Wall -Werror -Wfatal-errors doubleQ.c functions.h mazeEnv.h qlearning.h choose_action.h doubleQlearning.h dfs.h -lm

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c -lm

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c -lm

qlearning.o : qlearning.c qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h -lm

choose_action.o : choose_action.c choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h -lm

doubleQlearning.o : doubleQlearning.c doubleQlearning.h
	gcc -c -Wall -Werror -Wfatal-errors doubleQlearning.c doubleQlearning.h -lm

dfs.o : dfs.c dfs.h mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c dfs.h mazeEnv.h -lm

clean :
	rm -f doubleQ.o functions.o mazeEnv.o qlearning.o choose_action.o doubleQlearning.o dfs.o