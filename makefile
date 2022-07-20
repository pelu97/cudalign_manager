main: execution parserHeader profiler.c
	gcc -g ./src/parser.o ./src/execution.o profiler.c -Wall -o profiler


parserHeader: ./src/parser.c
	gcc -c ./src/parser.c -o ./src/parser.o

# data: ./src/data.c
# 	gcc -c ./src/data.c -o ./src/data.o



execution: ./src/execution.c
	# gcc -c ./src/execution.c -o ./src/execution.o
	gcc -c ./src/execution.c -o ./src/execution.o
