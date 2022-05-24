prog: main.o functions.o mazeEnv.o qlearning.o choose_action.o choose_action_sarsa.o choose_action_doubleQ.o doubleQlearning.o dfs.o
	gcc -o prog main.o functions.o mazeEnv.o qlearning.o choose_action.o choose_action_sarsa.o choose_action_doubleQ.o doubleQlearning.o dfs.o -lm

main.o: main.c functions.h mazeEnv.h qlearning.h choose_action.h choose_action_sarsa.h choose_action_doubleQ.h doubleQlearning.h dfs.h
	gcc -c -Wall -Werror -Wfatal-errors main.c functions.h mazeEnv.h qlearning.h choose_action.h choose_action_sarsa.h choose_action_doubleQ.h doubleQlearning.h dfs.h -lm

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c -lm

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c -lm

qlearning.o : qlearning.c qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h -lm

choose_action_sarsa.o : choose_action_sarsa.c choose_action_sarsa.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action_sarsa.c choose_action_sarsa.h -lm

choose_action_doubleQ.o : choose_action_doubleQ.c choose_action_doubleQ.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action_doubleQ.c choose_action_doubleQ.h -lm

choose_action.o : choose_action.c choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h -lm

doubleQlearning.o : doubleQlearning.c doubleQlearning.h
	gcc -c -Wall -Werror -Wfatal-errors doubleQlearning.c doubleQlearning.h -lm

dfs.o : dfs.c dfs.h mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c dfs.h mazeEnv.h -lm

clean :
	rm -f main.o functions.o mazeEnv.o qlearning.o choose_action.o choose_action_sarsa.o choose_action_doubleQ.o doubleQlearning.o dfs.o