CC = g++

all:
	$(CC) main.cpp grafo.cpp superNo.cpp arestas.cpp -Wall -Werror -O3 -g3 -o main

clean:
	rm main