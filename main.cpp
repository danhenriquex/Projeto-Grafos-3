#include "grafo.h"
#include "result.h"

/*
    Universidade Federal da Paraíba
    Trabalho da disciplina de Grafos
    Tema: Implementação e análise empı́rica do algoritmo de Karger
    Linguagem Utilizada: C++ e Python.
    Desenvolvido por:
    
        Arthur Ricardo 20170033039
        Danilo Henrique 20170140478
*/

int main( void ) {

    Grafo grafo = Grafo("./instancias/in/graph_type1_2");
    srand(time(0));
    int k = 0;
    const int optimalSolution = 2;
    const int maxItr = 10000;

    Result current = Result();
    Result best = Result();
    
    printf("\n=====Karger====\n");

    for ( int n = 5; n < 100; n=n+5 ) {
      k = 0;
      for ( int j = 0; j < maxItr; ++j ) {

          current = Result();
          best = Result();

          for ( int l = 0; l < n; ++l ) {
              current = grafo.kargerAlgorithm();
              
              if ( current.arestas_.size() < best.arestas_.size() || best.arestas_.size() == 0 ) {
                  best = current;
              }
          }

          if ( int(best.arestas_.size()) == optimalSolution ) {
              ++k;
          }
      }

      std::cout << "Best: " << best.arestas_.size() << std::endl;

      double result = (double) k / maxItr;

      std::cout << "Optimal Solution: " << result * 100 << "% " << " k: " << k << " n: " << n << std::endl;

      printf("\n");

      std::ofstream file;
      file.open("./resultados/resultados_type2_3_karge.txt", std::ios::app);
      file << n << " " << result << std::endl;
      file << "\n";
      file.close();

      if ( result == 1 ) {
        break;
      }
    }

  

    printf("\n=====Random====\n");

    Result currentRandom = Result();
    Result bestRandom = Result();

    k = 0;

    for ( int n = 5; n < 100; n=n+5 ) {
      k = 0;
      for ( int j = 0; j < maxItr; ++j ) {

          currentRandom = Result();
          bestRandom = Result();

          for ( int k = 0; k < n; ++k ) {
              currentRandom = grafo.randomizedNaiveAlgorithm();
              
              if ( currentRandom.arestas_.size() < bestRandom.arestas_.size() || bestRandom.arestas_.size() == 0 ) {
                  bestRandom = currentRandom;
              }
          }

          if ( int(bestRandom.arestas_.size()) == optimalSolution ) {
              ++k;
          }
      }

      std::cout << "Best: " << bestRandom.arestas_.size() << std::endl;

      double result = (double) k / maxItr;

      std::cout << "Optimal Solution: " << result * 100 << "% " << " k: " << k << " n: " << n << std::endl;

      printf("\n");

      std::ofstream file;
      file.open("./resultados/resultados_type2_3_random.txt", std::ios::app);
      file << n << " " << result << std::endl;
      file << "\n";
      file.close();
    }
    
    printf("\n");    

    return 0;
} 