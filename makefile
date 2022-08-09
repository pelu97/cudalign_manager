main: manager.c parser execution analyser profiler parameter cleanup
	gcc -g ./src/parser.o ./src/execution.o ./src/analyser.o ./src/profiler.o ./src/parameter.o ./src/cleanup.o manager.c -Wall -o manager


parser: ./src/parser.c
	gcc -c ./src/parser.c -o ./src/parser.o

# data: ./src/data.c
# 	gcc -c ./src/data.c -o ./src/data.o


execution: ./src/execution.c
	# gcc -c ./src/execution.c -o ./src/execution.o
	gcc -c ./src/execution.c -o ./src/execution.o


analyser: ./src/analyser.c
	gcc -c ./src/analyser.c -o ./src/analyser.o


profiler: ./src/profiler.c
	gcc -c ./src/profiler.c -o ./src/profiler.o

parameter: ./src/parameter.c
	gcc -c ./src/parameter.c -o ./src/parameter.o

cleanup: ./src/cleanup.c
	gcc -c ./src/cleanup.c -o ./src/cleanup.o
