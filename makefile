main: functions.o mazeEnv.o qlearning.o choose_action.o
	gcc -o main functions.o mazeEnv.o qlearning.o choose_action.o

functions.o : environnement/CMaze-main/functions.c environnement/CMaze-main/functions.h
	gcc -c -Wall -Werror -Wfatal-errors environnement/CMaze-main/functions.c

mazeEnv.o : environnement/CMaze-main/mazeEnv.c environnement/CMaze-main/mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors environnement/CMaze-main/mazeEnv.c

qlearning.o : agent/qlearning.c agent/qlearning.h
	gcc -c -Wall -Werror -Wfatal-errors agent/qlearning.c agent/qlearning.h

choose_action.o : agent/choose_action.c agent/choose_action.h
	gcc -c -Wall -Werror -Wfatal-errors agent/choose_action.c agent/choose_action.h

clean :
	rm -f main functions.o mazeEnv.o qlearning.o choose_action.o