main: manager.c parser execution analyser profiler parameter cleanup base
	gcc -g ./src/parser.o ./src/execution.o ./src/analyser.o ./src/profiler.o ./src/parameter.o ./src/cleanup.o ./src/base.o manager.c -Wall -o manager


parser: ./src/parser.c
	gcc -c ./src/parser.c -o ./src/parser.o -Wall

# data: ./src/data.c
# 	gcc -c ./src/data.c -o ./src/data.o


base: ./src/base.c
	gcc -c ./src/base.c -o ./src/base.o -Wall

execution: ./src/execution.c
	gcc -c ./src/execution.c -o ./src/execution.o -Wall


analyser: ./src/analyser.c
	gcc -c ./src/analyser.c -o ./src/analyser.o -Wall


profiler: ./src/profiler.c
	gcc -c ./src/profiler.c -o ./src/profiler.o -Wall

parameter: ./src/parameter.c
	gcc -c ./src/parameter.c -o ./src/parameter.o -Wall

cleanup: ./src/cleanup.c
	gcc -c ./src/cleanup.c -o ./src/cleanup.o -Wall

dummy:
	gcc ./dummy_program.c -o dummy_program -Wall
