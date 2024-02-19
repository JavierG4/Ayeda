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

Latice::Latice(int n, int frontera, std::string fichero) {
  //std::cout << "Latice constructor" << n <<std::endl; // Add this line
  frontera_ = frontera;
  if (fichero == " ") {
    if (frontera == 0 || frontera == 1) { 
      numero_celulas_ = n + 2;
      latice_.resize(n + 2);
      for ( int i = 1; i < n + 1; i++) { 
        if (n/2 == i) {
          latice_[i] = new Celula(Posicion(i), Estado(1));
        } else {
          latice_[i] = new Celula(Posicion(i), Estado(0));
        }
      }
      if (frontera == 0) {
        latice_[0] = new Celula(Posicion(0), Estado(0));
        latice_[n + 1] = new Celula(Posicion(n + 1), Estado(0));
      } else {
        latice_[0] = new Celula(Posicion(0), Estado(1));
        latice_[n + 1] = new Celula(Posicion(n + 1), Estado(1));
      }
    } else {
      numero_celulas_ = n;
      latice_.resize(n);
      for ( int i = 0; i < n; i++) { 
        if (n/2 == i) {
          latice_[i] = new Celula(Posicion(i), Estado(1));
        } else {
          latice_[i] = new Celula(Posicion(i), Estado(0));
        }
      }
    }
  } else {
    //std::cout << fichero << std::endl;
    std::ifstream file(fichero);
    //std::cout << numero_celulas << std::endl;
    if (frontera == 0) {
      numero_celulas_ = n + 2;
      latice_.resize(n + 2);
      latice_[0] = new Celula(Posicion(0), Estado(0));
      latice_[n + 1] = new Celula(Posicion(n + 1), Estado(0)); // CORREGIR
      for (int i = 1; i < n + 1;i++) {
        int estado;
        file >> estado;
        latice_[i] = new Celula(Posicion(i), Estado(estado));
      }
    } else if ( frontera == 1) {
      numero_celulas_ = n + 2;
      latice_.resize(n + 2);
      latice_[0] = new Celula(Posicion(0), Estado(1));
      latice_[n + 1] = new Celula(Posicion(n + 1), Estado(1));
      for (int i = 1; i < n + 1;i++) {
        int estado;
        file >> estado;
        latice_[i] = new Celula(Posicion(i), Estado(estado));
      }
    } else {
      numero_celulas_ = n;
      latice_.resize(n);
      for (int i = 0; i < n;i++) {
        int estado;
        file >> estado;
        latice_[i] = new Celula(Posicion(i), Estado(estado));
      }
    }
  }
}

Latice::~Latice() {
  for (int i = 0; i < numero_celulas_; i++) {
    delete latice_[i];
  }
}

void Latice::NextGeneration() {
  if ( frontera_ == 0 || frontera_ == 1) {
    int contador = 1;  
    char input;
    while (true) {
      input = getch();
      if (input != ' ') {
        break;
      }
      for (int i = 1; i < numero_celulas_ - 1; i++ ) {
        latice_[i] -> SetEstadoSiguiente(latice_[i] -> NextState(*this)); 
      }
      for (int e = 1; e < numero_celulas_ - 1; e++ ) {
        latice_[e] -> UpdateState();
      }
      PrintLatice(contador);
      contador++;
    }
  } else { // periodica
    char input;
    int contador = 1;
    while (true) {
      input = getch(); 
      if (input != ' ') {
        break;
      }
      for (int i = 0; i < numero_celulas_; i++ ) {
        latice_[i] -> SetEstadoSiguiente(latice_[i] -> NextState(*this)); 
      }
      for (int e = 0; e < numero_celulas_; e++ ) {
        latice_[e] -> UpdateState();
      }
      PrintLatice(contador);
      contador++;
    }
  }
}

void Latice::PrintLatice(int x) {
  for (int i = 0; i < numero_celulas_; i++) {
    if (latice_[i] -> GetEstado().GetEstado() == 1) { 
      std::cout << "X";
    } else {
      std::cout << " ";
    }
  }
  std::cout << "   G( " << x << " )  ";
  std::cout << std::endl;
}

int Latice::GetNumCelula() {
  return numero_celulas_;
}

int Latice::GetFrontera() {
  return frontera_;
} 

Celula& Latice::operator[](int i) {
  return *latice_[i];
}

