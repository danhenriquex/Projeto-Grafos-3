CC = g++

all:
	$(CC) main.cpp grafo.cpp superNo.cpp -g3 -o main

clean:
	rm main