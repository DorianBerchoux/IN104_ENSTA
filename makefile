prog: dfs.o functions.o mazeEnv.o
	gcc -o prog dfs.o functions.o mazeEnv.o

dfs.o : environnement/CMaze-main/dfs.c environnement/CMaze-main/mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors environnement/CMaze-main/dfs.c

functions.o : environnement/CMaze-main/functions.c environnement/CMaze-main/functions.h
	gcc -c -Wall -Werror -Wfatal-errors environnement/CMaze-main/functions.c

mazeEnv.o : environnement/CMaze-main/mazeEnv.c environnement/CMaze-main/mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors environnement/CMaze-main/mazeEnv.c

clean :
	rm -f prog dfs.o functions.o mazeEnv.o