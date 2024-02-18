#include "latice.h"
#include <iostream> // Add this line
#include <termios.h>
#include <unistd.h>

int getch() {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

Latice::Latice(int filas, int columnas, int frontera) {
  frontera_ = frontera;
  if (frontera_ == 2 || frontera_ == 3 ||frontera_ == 4) { 
    numero_celulas_ = columnas * filas;
    latice_ = Matriz(filas, columnas, numero_celulas_);
    for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
        latice_[i][j] = new Celula(Posicion(i,j),Estado(PreguntarEstado(i, j)));
      }
    }
  } else if (frontera_ == 0 || frontera_ == 1) {
    filas = filas + 2;
    columnas = columnas + 2;
    numero_celulas_ = columnas * filas;
    latice_ = Matriz(filas, columnas, numero_celulas_);
    for (int i = 1; i < filas - 1; i++) {
      for (int j = 1; j < columnas - 1; j++) {
        latice_[i][j] = new Celula(Posicion(i,j),Estado(PreguntarEstado(i -1 , j - 1)));
      }
    }
    if ( frontera == 0 ) { 
      for ( int i = 0; i < columnas; i++) { // borde de arriba
        latice_[0][i] = new Celula(Posicion(0,i),Estado(0));
      }
      for ( int i = 0; i < filas; i++){ // borde de la izquierda
        latice_[i][0] = new Celula(Posicion(0,i),Estado(0));
      }
      for ( int i = 0; i < filas; i++){ // borde de la derecha
        latice_[i][columnas - 1] = new Celula(Posicion(0,i),Estado(0));
      }
      for ( int i = 0; i < columnas; i++) { // borde de abajo
        latice_[filas - 1][i] = new Celula(Posicion(0,i),Estado(0));
      }
    }
    if ( frontera == 1 ) { 
      for ( int i = 0; i < columnas; i++) { // borde de arriba
        latice_[0][i] = new Celula(Posicion(0,i),Estado(1));
      }
      for ( int i = 0; i < filas; i++){ // borde de la izquierda
        latice_[i][0] = new Celula(Posicion(0,i),Estado(1));
      }
      for ( int i = 0; i < filas; i++){ // borde de la derecha
        latice_[i][columnas - 1] = new Celula(Posicion(0,i),Estado(1));
      }
      for ( int i = 0; i < columnas; i++) { // borde de abajo
        latice_[filas - 1][i] = new Celula(Posicion(0,i),Estado(1));
      }
    }
  }
}

Latice::~Latice() {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      delete latice_[i][j];
    }
  }
}


int Latice::PreguntarEstado(int x, int y) {
  int estado;
  std::cout << "Introduzca el estado de la célula: (" << x << ", " << y << ") ";
  std::cin >> estado;
  return estado;
}


/*
‘x' : Finaliza la ejecución del programa
‘n’ : Calcula y muestra la siguiente generación
‘L’ : Calcula y muestra las siguientes cinco generaciones
‘c’ : Los comandos ‘n’ y ‘L’ dejan de mostrar el estado del tablero y sólo se muestra
la población, esto es, el número de células en estado «viva»
‘s’ : Salva el tablero a un fichero
*/
void Latice::NextGeneration() {
  if ( frontera_ == 0 || frontera_ == 1) {
    bool flagc = 0;
    int contador = 1;  
    char input;
    while (true) {
      int veces = 0;
      input = getch();
      if (input == 'x') {
        break;
      } else if ( input == 'n') {
        veces = 1;
      } else if (input == 'L') {
        veces = 5;
      } else if ( input == 'c' ) {
        flagc = 1;
      } else if (input == 's') { // guardar en fichero
        // Escribir
      }
      //std::cout << latice_.GetFilas() << "-" << latice_.GetColumnas() << std::endl;
      for (int o = 0; o < veces ; o++) {
        int numero = 0;
        int col = latice_.GetColumnas() - 1;
        int fil = latice_.GetFilas() - 1;
        std::cout << "col: " << col << " fil: " << fil << std::endl;
        for (int i = 1; i < fil; i++ ) {
          for (int j = 1; j < col; j++) {
            //std::cout << i << " _ " << j << std::endl;
            latice_[i][j] -> SetEstadoSiguiente(latice_[i][j] -> NextState(*this)); 
          }
        }
        for (int e = 1; e < latice_.GetFilas() - 1; e++ ) {
          for (int r = 1; r < latice_.GetColumnas() - 1; r++) { 
            latice_[e][r] -> UpdateState();
          }
        }
        if (flagc == 0) { 
          std::cout << "G ( " << contador << " ) " << std::endl;
          PrintLatice();
          contador++;
        } else if (flagc == 1) {
          std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
          //PrintLatice();
          contador++;
        }
      }
    }     
  } else if ( frontera_ == 2 || frontera_ == 3 ) {
    bool flagc = 0;
    int contador = 1;  
    char input;
    while (true) {
      int veces = 0;
      input = getch();
      if (input == 'x') {
        break;
      } else if ( input == 'n') {
        veces = 1;
      } else if (input == 'L') {
        veces = 5;
      } else if ( input == 'c' ) {
        flagc = 1;
      } else if (input == 's') { // guardar en fichero
        // Escribir
      }
      for (int o = 0; o < veces ; o++) { 
        for (int i = 0; i < latice_.GetFilas(); i++ ) {
          for (int j = 0; j < latice_.GetColumnas(); j++) { 
            //std::cout << "j" << std::endl;
            latice_[i][j] -> SetEstadoSiguiente(latice_[i][j] -> NextState(*this)); 
          }
        }
        for (int e = 0; e < latice_.GetFilas(); e++ ) {
          for (int r = 0; r < latice_.GetColumnas(); r++) { 
            latice_[e][r] -> UpdateState();
          }
        }
        if (flagc == 0) { 
          std::cout << "G ( " << contador << " ) "  <<std::endl;
          PrintLatice();
          contador++;
        } else if (flagc == 1) {
          std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
          //PrintLatice();
          contador++;
        }
      }
    }    
  } else if ( frontera_ == 4 ) {

  }
}

void Latice::PrintInstrucciones() {
  std::cout << "‘x' : Finaliza la ejecución del programa" << std::endl;
  std::cout << "‘n’ : Calcula y muestra la siguiente generación" << std::endl;
  std::cout << "‘L’ : Calcula y muestra las siguientes cinco generaciones" << std::endl;
  std::cout << "‘c’ : Los comandos ‘n’ y ‘L’ dejan de mostrar el estado del tablero y sólo se muestra" << std::endl;
  std::cout << "la población, esto es, el número de células en estado «viva»" << std::endl;
  std::cout << "‘s’ : Salva el tablero a un fichero" << std::endl;
}

void Latice::PrintLatice() {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      std::cout << latice_[i][j] -> GetEstado().GetEstado() << " ";
    }
    std::cout << std::endl;
  }
}

int Latice::GetNumCelula() {
  return numero_celulas_;
}

int Latice::GetFrontera() {
  return frontera_;
} 

/*Celula& Latice::operator[](int i) {
  return *latice_[i];
}
*/

std::size_t Latice::Population()  {
  int population = 0;
  for ( int i = 0; i < latice_.GetFilas(); i++ ) { // Accedo a cada fila , es decir cada Myvector<celula*>
    for ( int j = 0; j < latice_[i].size(); j++ ) { // Accedo a cada columna, es decir cada celula* y accedo a lo que apunta y le hago un get
      if ( latice_[i][j] -> GetEstado().GetEstado() == 1 ) {
        population++;
      }
    }
  }
  return population;
}

/*
Latice::Latice(int filas, int columnas, int frontera) {
  numero_celulas_ = columnas * filas;
  frontera_ = frontera;
  //std::cout << "j2" ;
  latice_ = Matriz(filas, columnas, numero_celulas_);
  //std::cout << "i" ;
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      //std::cout << "j" ;
      latice_[i][j] = new Celula(Posicion(i,j),Estado(PreguntarEstado(i, j)));
    }
  }
}
*/

bool Latice::Alrededor(int numero) {
  if (numero == 1) {
    for ( int i = 0; i < latice_[0].size(); i++) {
      if ( latice_[0][i] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 2) {
    for (int i = 0; i <latice_.GetColumnas();i++) {
      if ( latice_[i][0] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 3) {
    for (int i = 0; i < latice_[latice_.GetFilas() - 1].size(); i++) {
      if ( latice_[latice_.GetFilas() - 1][i] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 4) {
    for (int i = 0; i < latice_.GetColumnas(); i++) {
      if ( latice_[i][latice_.GetColumnas() - 1] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  }
}

Matriz Latice::GetMatriz() {
  return latice_;
}