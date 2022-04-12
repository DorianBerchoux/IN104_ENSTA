prog: dfs.o functions.o mazeEnv.o
	gcc -o prog dfs.o functions.o mazeEnv.o

dfs.o : environnement/dfs.c environnement/mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o : environnement/functions.c environnement/functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c

mazeEnv.o : environnement/mazeEnv.c environnement/mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

clean :
	rm -f prog dfs.o functions.o mazeEnv.o