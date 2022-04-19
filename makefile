main: functions.o mazeEnv.o qlearning.o choose_action.o
	gcc -o main functions.o mazeEnv.o qlearning.o choose_action.o

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

qlearning.o : qlearning.c qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors qlearning.c qlearning.h

choose_action.o : choose_action.c choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors choose_action.c choose_action.h

clean :
	rm -f main functions.o mazeEnv.o qlearning.o choose_action.o