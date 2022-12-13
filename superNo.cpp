#include "superNo.h"

SuperNo::SuperNo( void ) {}

SuperNo::SuperNo( const int& i ) {
  this->noId_ = i;
  this->vertices_.push_back( i ); 
  
}