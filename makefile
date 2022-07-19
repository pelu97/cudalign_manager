main: ./src/parser.o
	gcc -g ./src/parser.o profiler.c -Wall -o profiler

parserHeader:
	gcc -c ./src/parser.c -o ./src/parser.o
