#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <bits/stdc++.h>

#include "arestas.h"
#include "superNo.h"

using namespace std;

class Grafo {
  public:
    Grafo( void );
    Grafo( const string& file );
    
    void dfs( const int& vertice );
    void bfs( const int& vertice );
    void busca( const int& edge, int* PE, int* PS, int* Pai );
    void kargerAlgorithm( void );
    void randomizedNaiveAlgorithm( void );

    void showMatrix( void );
    void showAdjacency( const int& edge );
    void showAdjacency( void );
    void mergeSuperNo( const int& i, const int& j, std::vector<SuperNo>& supernos );
    Arestas getRandomAresta( const std::vector<Arestas>& arestas);
    SuperNo getRandomVertice( const std::vector<SuperNo>& vertices );
    std::vector<Arestas> getArestas( const SuperNo& superno1, const SuperNo& superno2 );

    inline int getSize( void ) const;

    int changeCharToInt( const char& ch );

  private:
    int size_;
    std::vector<std::vector<int>> matrix_;
    std::list<int>* adj_;
};