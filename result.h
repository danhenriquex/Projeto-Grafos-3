#ifndef RESULT_H
#define RESULT_H

#include "arestas.h"
#include "superNo.h"

class Result {
  public:
    Result( void );
    Result( const SuperNo& superno1, const SuperNo& superno2, const std::vector<Arestas>& arestas );

    SuperNo superno1_;
    SuperNo superno2_;
    std::vector<Arestas> arestas_;
};

#endif