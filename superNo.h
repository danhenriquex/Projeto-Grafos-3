#ifndef SUPERNO_H
#define SUPERNO_H

#include <string>
#include "arestas.h"

class SuperNo {
  public:
    SuperNo( void );
    SuperNo ( const int& i );

    std::vector<int> vertices_;
    std::vector<Arestas> arestas_;
    int noId_;
    std::string color_;
};

#endif