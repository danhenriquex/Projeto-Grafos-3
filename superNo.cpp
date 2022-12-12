#include "superNo.h"

SuperNo::SuperNo( void ) {}

SuperNo::SuperNo( const int& i ) {
  this->noId_ = i;
}

SuperNo::SuperNo( const int& i, const int& j ) {
  this->vertices_.push_back( i );
  this->vertices_.push_back( j );

  this->noId_ = i + j + 7;
}