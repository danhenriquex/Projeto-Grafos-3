CC = g++

all:
	$(CC) main.cpp grafo.cpp superNo.cpp arestas.cpp result.cpp -Wall -Werror -g3 -o main

clean:
	rm main