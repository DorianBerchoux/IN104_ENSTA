prog: dfs.o functions.o mazeEnv.o
	gcc -o prog dfs.o functions.o mazeEnv.o

dfs.o : dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Wfatal-errors functions.c

mazeEnv.o : mazeEnv.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

clean :
	rm -f prog dfs.o functions.o mazeEnv.o