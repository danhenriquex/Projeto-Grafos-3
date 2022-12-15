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

      for ( int i = 0; i < int(value.length()); ++i ) {
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

std::vector<Arestas> Grafo::getArestas( const SuperNo& superno1, const SuperNo& superno2 ) {
  std::vector<Arestas> arestas;

  for ( int i = 0; i < int(superno1.vertices_.size()); ++i ) {
    for ( int j = 0; j < int(superno2.vertices_.size()); ++j ) {
      if ( this->matrix_[superno1.vertices_[i]][superno2.vertices_[j]] == 1 ) {
        Arestas aresta = Arestas( superno1.vertices_[i], superno2.vertices_[j] );
        arestas.push_back( aresta );
      }
    }
  }

  return arestas;
}

void Grafo::randomizedNaiveAlgorithm( void ) {
  srand(time(0));

  std::vector<SuperNo> supernos;
  SuperNo superno1 = SuperNo( 0 );
  SuperNo superno2 = SuperNo( 1 );

  int k = 0;

  for ( int i = 2; i < int(this->matrix_.size()); ++i ) {

    k = rand() % this->matrix_.size();

    if ( k % 2 == 0 ) {
      superno1.vertices_.push_back( i );
    } 

    if ( k % 2 != 0 ) {
      superno2.vertices_.push_back( i );
    } 
  } 

  supernos.push_back( superno1 );
  supernos.push_back( superno2 );

  const std::vector<Arestas> arestas = this->getArestas( superno1, superno2 );

  for (int i = 0; i < int(supernos.size()); i++){
    std::cout << "SuperNo"<< i << ":";
    for (int j = 0; j < int(supernos[i].vertices_.size()); j++){
      std::cout<< supernos[i].vertices_[j] + 1<<", ";
    }
    std::cout << std::endl;
  }

  for ( auto const& edge : arestas ) {
    std::cout << "Aresta: " << edge.i_ + 1 << " " << edge.j_ + 1 << std::endl;
  }
}

void Grafo::kargerAlgorithm( void ) {
  std::vector<Arestas> arestas;
  std::vector<SuperNo> supernos;

  for ( int i = 0; i < this->getSize(); ++ i ) {
    SuperNo superno = SuperNo(i);
    supernos.push_back( superno );

    for ( int j = 0; j < this->getSize(); ++j ) {

      if ( this->matrix_[i][j] == 1 && i != j ) {

        Arestas aresta = Arestas( i, j );
        arestas.push_back( aresta );

      }
    }
  }

  int maior = 0;
  int menor = 0;

  while ( supernos.size() > 2 ) {
    Arestas currentEdge = this->getRandomAresta( arestas );

    if (currentEdge.i_ < currentEdge.j_){
      menor = currentEdge.i_;
      maior = currentEdge.j_;
    }else{
      menor = currentEdge.j_;
      maior = currentEdge.i_;
    }
    
    this->mergeSuperNo(menor, maior, supernos );

    for (auto& edge : arestas){

      if(edge.i_== maior){
        edge.i_ = menor;
      }
      if(edge.j_== maior){
        edge.j_ = menor;
      }
      if(edge.i_ > maior){
      edge.i_ = edge.i_ -1;
      }
      if(edge.j_ > maior){
        edge.j_ = edge.j_ -1;
      }
    }
    int i = 0;
    while (i < int(arestas.size())){
      if(arestas[i].i_ == arestas[i].j_ || arestas[i].j_ == arestas[i].i_){
        arestas.erase(arestas.begin()+i);
        i = 0 ;
      }else{
        i++;
      }
    }
  }

  for (int i = 0; i < int(supernos.size()); i++){
    std::cout << "SuperNo"<< i << ":";
    for (int j = 0; j < int(supernos[i].vertices_.size()); j++){
      std::cout<< supernos[i].vertices_[j] + 1<<", ";
    }
    std::cout << std::endl;
  }

  const std::vector<Arestas> arestasAux = this->getArestas( supernos[0], supernos[1] );

  for ( auto const& edge : arestasAux ) { 
    std::cout << "Aresta: " << edge.i_ + 1 << " " << edge.j_ + 1 << std::endl;
  }
}

void Grafo::mergeSuperNo( const int& i, const int& j, std::vector<SuperNo>& supernos ) {

  for (auto& edge : supernos[j].vertices_){
    supernos[i].vertices_.push_back(edge);
  }
  supernos.erase(supernos.begin()+j);

}

Arestas Grafo::getRandomAresta( const std::vector<Arestas>& arestas ) {
  int randomIndex = rand() % arestas.size();
  return arestas[randomIndex];
}

SuperNo Grafo::getRandomVertice( const std::vector<SuperNo>& vertices ) {
  srand(time(NULL));
  
  int randomIndex = rand() % vertices.size();
  return vertices[randomIndex];
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