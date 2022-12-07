#ifndef SUPERNO_H
#define SUPERNO_H

#include "arestas.h"

class SuperNo {
  public:
    SuperNo( void );
    SuperNo ( const int& noId );

    std::vector<int> vertices_;
    std::vector<Arestas> arestas_;
    int noId_;
};

#endif