#ifndef ARESTAS_H
#define ARESTAS_H

#include <vector>

class Arestas {
  public:
    Arestas( void ) {};
    // Arestas ( const SuperNo& i, const SuperNo& j );
    Arestas ( const int& i, const int& j );

    int i_;
    int j_;
};

#endif