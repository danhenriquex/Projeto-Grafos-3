#include "superNo.h"

SuperNo::SuperNo( void ) {}

SuperNo::SuperNo( const int& noId ) : noId_(noId) {
  this->vertices_.push_back( noId ); 
}