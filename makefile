main: profiler.c parser execution analyser
	gcc -g ./src/parser.o ./src/execution.o ./src/analyser.o profiler.c -Wall -o profiler


parser: ./src/parser.c
	gcc -c ./src/parser.c -o ./src/parser.o

# data: ./src/data.c
# 	gcc -c ./src/data.c -o ./src/data.o


execution: ./src/execution.c
	# gcc -c ./src/execution.c -o ./src/execution.o
	gcc -c ./src/execution.c -o ./src/execution.o

analyser: ./src/analyser.c
	gcc -c ./src/analyser.c -o ./src/analyser.o
