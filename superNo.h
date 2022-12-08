#ifndef SUPERNO_H
#define SUPERNO_H

#include "arestas.h"
#include <vector>

class SuperNo {
  public:
    SuperNo( void );
    SuperNo( const int& i );
    SuperNo( const SuperNo& i, const SuperNo& j );

    std::vector<SuperNo> vertices_;
    std::vector<Arestas> arestas_;
    int noId_;
};

#endif