#ifndef SUPERNO_H
#define SUPERNO_H

#include <vector>

class Arestas {
  public:
    Arestas( void ) {};
    Arestas ( const int& i, const int& j );

    int i_;
    int j_;
};

class SuperNo {
  SuperNo( void ) {};

  private:
    std::vector<int> vertices;
    std::vector<Arestas> arestas;
};

#endif