#include "grafo.h"
#include "result.h"

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

    Grafo grafo = Grafo("./arquivos_testes/graph_type2_1.txt");
    srand(time(0));

    Result current = Result();
    Result best = Result();
    
    printf("\n=====Karger====\n");


    for ( int i = 0; i < 1000; ++i ) {

      current = Result();
      best = Result();

      for ( int j = 0; j < 10; ++j ) {
        current = grafo.kargerAlgorithm();
        
        if ( current.arestas_.size() < best.arestas_.size() || best.arestas_.size() == 0 ) {
            best = current;
        }
      }
    }

    std::cout << "Best: " << best.arestas_.size() << std::endl;

    for ( int i = 0; i < int(best.superno1_.vertices_.size()); ++i ) {
        std::cout << best.superno1_.vertices_[i] + 1 <<  " ";
    }

    printf("\n");
    
    for ( int i = 0; i < int(best.superno2_.vertices_.size()); ++i ) {
        std::cout << best.superno2_.vertices_[i] + 1 << " ";
    }

    printf("\n=====Random====\n");

    Result currentRandom = Result();
    Result bestRandom = Result();
    

    for ( int i = 0; i < 1000; ++i ) {

      currentRandom = Result();
      bestRandom = Result();

      for ( int j = 0; j < 10; ++j ) {
        currentRandom = grafo.randomizedNaiveAlgorithm();
        
        if ( currentRandom.arestas_.size() < bestRandom.arestas_.size() || bestRandom.arestas_.size() == 0 ) {
            bestRandom = currentRandom;
        }
      }
    }

    std::cout << "Best: " << bestRandom.arestas_.size() << std::endl;

    for ( int i = 0; i < int(bestRandom.superno1_.vertices_.size()); ++i ) {
        std::cout << bestRandom.superno1_.vertices_[i] + 1 <<  " ";
    }

    printf("\n");
    
    for ( int i = 0; i < int(bestRandom.superno2_.vertices_.size()); ++i ) {
        std::cout << bestRandom.superno2_.vertices_[i] + 1 << " ";
    }

    printf("\n");

    return 0;
} 