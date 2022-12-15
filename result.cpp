#include "result.h"

Result::Result( void ) {
  this->superno1_ = SuperNo();
  this->superno2_ = SuperNo();
  this->arestas_ = std::vector<Arestas>();
}

Result::Result( const SuperNo& superno1, const SuperNo& superno2, const std::vector<Arestas>& arestas ) {
  this->superno1_ = superno1;
  this->superno2_ = superno2;
  this->arestas_ = arestas;
}