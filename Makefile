build:
	gcc -g -o tema1 tema1.c functiiTema1.c
run:
	./tema1
clean:
	rm lista2
valgrind:
	valgrind --leak-check=yes --track-origins ./tema1
