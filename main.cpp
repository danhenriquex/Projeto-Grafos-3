#include "grafo.h"

/*
    Universidade Federal da Paraíba
    Trabalho da disciplina de Grafos
    Tema: Busca em Grafos
    Linguagem Utilizada: C++.
    Desenvolvido por:
    
        Arthur Ricardo, 20170033039
        Danilo Henrique, 20170140478
*/

int main( void ) {

    Grafo grafo = Grafo("./arquivos_testes/graph_type1_1.txt");

    grafo.showAdjacency();
    
    grafo.kargerAlgorithm();
    
    return 0;
} 