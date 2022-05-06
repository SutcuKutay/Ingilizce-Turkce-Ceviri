all: compile run
compile:
	gcc -g -I ./include -c ./src/main.c -o ./lib/main.o
	gcc -g -o ./bin/uyg ./lib/main.o ./lib/libfdr.a
run:
	./bin/uyg eng ./txt/input.txt ./txt/sozluk.txt
