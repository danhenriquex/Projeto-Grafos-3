#include "grafo.h"
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>
#include "superNo.h"


Grafo::Grafo( void ) {

}

Grafo::Grafo( const string& file ) {
   std::ifstream text(file);

  if ( text.is_open() ) {
    std::string value;
    text >> this->size_;
    while( !text.eof() ) {
      std::getline(text, value);

      bool resultado = value[0] == '0' || value[0] == '1';

      if ( !resultado ) {
        this->adj_ = new std::list<int>[this->size_];
        continue;
      };

      std::vector<int> line;

      for ( int i = 0; i < value.length(); ++i ) {
        if ( value[i] == ' ') continue;
          line.push_back( this->changeCharToInt( value[i]) ); 
      }

      this->matrix_.push_back( line );
    }

    for ( int i = 0; i < this->getSize(); ++ i ) {
      for ( int j = 0; j < this->getSize(); ++j ) {
        if ( this->matrix_[i][j] == 1) {
          this->adj_[i].push_back( j );
        }
      }
    }
  }
}

void Grafo::kargerAlgorithm( void ) {
  auto criaArestas = []( const int& size ) {
    srand(time(0));

    int i, j;

    do {

      i = rand() % size;
      j = rand() % size;

    } while( i == j );

    Arestas no( i, j );

    return no;
  };

  auto x = criaArestas(10);
  std::cout << "x" << x.i_ << "y" << x.j_ << std::endl;

  if( this->matrix_[x.i_][x.j_] == 1 ) {
    std::cout << "entrou aqui" << std::endl;
  }

}

void Grafo::busca( const int& v, int* PE, int* PS, int* Pai ) {
  static int time = time + 1;
  PE[v] = time;

  for ( int edges : this->adj_[v] ) {
    if ( PE[edges] == 0 ) {
      if ( this->matrix_[v][edges] == 1 ) {
        this->matrix_[v][edges] = 2;
        this->matrix_[edges][v] = 2;
      }
      Pai[edges] = v;
      busca( edges, PE, PS, Pai );
    }else {
      if ( PS[edges] == 0 && edges != Pai[v] ) {
        if ( this->matrix_[v][edges] == 1 ) {
          this->matrix_[v][edges] = 3;
          this->matrix_[edges][v] = 3;
        }
      }
    }
  }

  time = time + 1;
  PS[v] = time;
}

void Grafo::dfs( const int& edge ) {
  int Profunidade_entrada[this->size_];
  int Profunidade_saida[this->size_];
  int Pai[this->size_];

  for ( int i = 0; i < this->size_; ++i ) {
    Profunidade_entrada[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Profunidade_saida[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Pai[i] = 0;
  }

  int v = 0;
  int time = 0;

  this->busca( edge, Profunidade_entrada, Profunidade_saida, Pai );
}

void Grafo::bfs( const int& edge ) {
  
  std::queue<int> fila;
  int Times[this->size_];
  int Nivel[this->size_];
  int Pai[this->size_];

  for ( int i = 0; i < this->size_; ++i ) {
    Times[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Nivel[i] = 0;
  }

  for ( int i = 0; i < this->size_; ++i ) {
    Pai[i] = 0;
  }

  int time = 1;
  fila.push(edge);
  
  Times[edge] = time;

  int v = 0 ;

  while (!fila.empty()){
    v = fila.front();

    fila.pop();

    for ( int edges : this->adj_[v] ) {
      if (Times[edges] == 0){
        if (this->matrix_[v][edges] == 1){
          this->matrix_[v][edges] = 2;
          this->matrix_[edges][v] = 2;
        }
        
        time = time + 1;
        Times[edges] = time;
        Pai[edges] = v;
        Nivel[edges] = Nivel[v] + 1;
        fila.push(edges);
      }else{
        if (Nivel[v] == Nivel[edges]){
          if(Pai[v] == Pai[edges]){
            if (this->matrix_[v][edges] == 1){
              this->matrix_[v][edges] = 3;
              this->matrix_[edges][v] = 3;
            }
          }else{
            if (this->matrix_[v][edges] == 1){
              this->matrix_[v][edges] = 4;
              this->matrix_[edges][v] = 4;
            }
          }
          
        }else{
          if (Nivel[edges] == Nivel[v]+1){
            if (this->matrix_[v][edges] == 1){
              this->matrix_[v][edges] =    5;
              this->matrix_[edges][v] = 5;
            }
          }
        }
      }
    }
  }
}

void Grafo::showAdjacency( const int& edge = 0 ) {
  std::cout << "vertice: " << edge << " => ";
    for ( int edges : this->adj_[edge] ) {
      std::cout << edges << " ";
    }
  std::cout << std::endl;
}

void Grafo::showAdjacency( void ) {
  for (int i = 0; i < this->getSize(); i++){
    std::cout << "vertice: " << i << " => ";
    for ( int edges : this->adj_[i] ) {
      std::cout << edges << " ";
    }
  std::cout << std::endl;
  }
}

void Grafo::showMatrix( void ) {
  for ( int i = 0; i < this->size_; i++ ) {
    for ( int j = 0; j < this->size_; j++ ) {
      std::cout << this->matrix_[i][j] << " ";
    }
    std::cout << endl;
  }
}


inline int Grafo::getSize( void ) const {
  return this->size_;
}

int Grafo::changeCharToInt( const char& ch ) {
  return int(ch) - 48;
}