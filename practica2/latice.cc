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
  if (frontera_ == 0 || frontera_ == 1) {
    filas += 2;
    columnas += 2;
  }
  numero_celulas_ = columnas * filas;
  latice_ = Matriz(filas, columnas, numero_celulas_);

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      int estado = 0;
      if (frontera_ == 2 || frontera_ == 3 || frontera_ == 4) {
        estado = PreguntarEstado(i, j);
      } else if (frontera_ == 0 || frontera_ == 1) {
        if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
          estado = frontera_;
        } else {
          estado = PreguntarEstado(i - 1, j - 1);
        }
      }
      latice_[i][j] = new Celula(Posicion(i, j), Estado(estado));
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
          for (int j = 0; j < latice_.GetColumnas() ; j++) { 
            //std::cout << "j" << std::endl;
            latice_[i][j] -> SetEstadoSiguiente(latice_[i][j] -> NextState(*this)); 
          }
        }
        for (int e = 0; e < latice_.GetFilas() ; e++ ) {
          for (int r = 0; r < latice_.GetColumnas() ; r++) { 
            latice_[e][r] -> UpdateState();
          }
        }
        Comprobar();
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
  }
}

void Latice::Comprobar() {
  int flag1 = Alrededor(1);
  int flag2 = Alrededor(2);
  int flag3 = Alrededor(3);
  int flag4 = Alrededor(4);
  std::cout << "Comprobando bordes" << std::endl;
  if (flag1) { //BORDE ARRIBA FILA
    std::cout << "Alrededor 1" << std::endl;
    Myvector vector_aux(latice_[0].size());
    for (int i = 0; i < latice_[0].size(); i++) {
      vector_aux[i] = new Celula(Posicion(latice_.GetIndiceInicial() - 1,i),Estado(0));
      latice_.Push_front(vector_aux);
    }
  }
  if (flag2) { //FILA DE ABAJO
    std::cout << "Alrededor 2" << std::endl;
    Myvector vector_aux(latice_[0].size());
    for (int i = 0; i < latice_[0].size(); i++) {
      vector_aux[i] = new Celula(Posicion(latice_[0].size(),i),Estado(0));
      latice_.Push_back(vector_aux);
    }
  }
  if (flag3) { //Columna izquierda
    std::cout << "Alrededor 3" << std::endl;
    for (int i = 0; i < latice_.GetFilas(); i++) {
      Celula* cell = new Celula(Posicion(i,latice_[0].GetIndiceInicial() - 1),Estado(0));
      latice_[i].push_front(cell);
    }
  }
  if (flag4) {
    std::cout << "Alrededor 4" << std::endl;
    for (int i = 0; i < latice_.GetFilas(); i++) {
      Celula* cell = new Celula(Posicion(i,latice_[i].size()),Estado(0));
      latice_[i].push_back(cell);
    }
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
  std::cout << latice_.GetIndiceInicial() << std::endl;
  std::cout << latice_[0].GetIndiceInicial() << std::endl;
  for (int i = latice_.GetIndiceInicial(); i < latice_.GetFilas(); i++) {
    for (int j = latice_[0].GetIndiceInicial(); j < latice_[i].size(); j++) {
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

Celula& Latice::operator[](Posicion pos) {
  return GetCell(pos.GetPosicionX(), pos.GetPosicionY());
}


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

Celula& Latice::GetCell(int i, int j) {
  int pos_x = i;
  int pos_y = j;
  if (frontera_ == 0 || frontera_ == 1) {
    return *latice_[i][j];
  } else if (frontera_ == 2) {
    if (i < 0 && j < 0) {
      return *latice_[latice_.GetFilas() - 1][latice_.GetColumnas() - 1];
    } else if (i < 0 && j >= latice_.GetColumnas()) {
      return *latice_ [latice_.GetFilas() - 1][0];
    }
    // Esquina inferior izquierda
    else if (i >= latice_.GetFilas()  && j < 0) {
      return *latice_[0][latice_.GetColumnas() - 1];
    }
    // Esquina inferior derecha
    else if (i >= latice_.GetFilas()  && j >= latice_.GetColumnas()) {
      return *latice_[0][0];
    }
    // Borde superior
    else if (i < 0) {
      return *latice_[latice_.GetFilas() - 1][j];
    }
    // Borde inferior
    else if (i >= latice_.GetFilas()) {
      return *latice_[0][j];
    }
    // Borde izquierdo
    else if (j < 0) {
      return *latice_[i][latice_.GetColumnas() - 1];
    }
    // Borde derecho
    else if (j >= latice_.GetColumnas()) {
      return *latice_[i][0];
    } else {
    return *latice_[i][j];
    }
  } else if (frontera_ == 3) {
    if (i == -1 && j == - 1) {
      return *latice_[0][0];
    } 
    //Arriba derecha
    else if (i == -1 && j == latice_.GetColumnas()) {
      return *latice_ [0][pos_y - 1];
    }
    // Esquina inferior izquierda
    else if (i == latice_.GetFilas() && j == -1) {
      return *latice_[pos_x - 1][0];
    }
    // Esquina inferior derecha
    else if (i == latice_.GetFilas()  && j == latice_.GetColumnas()) {
      return *latice_[pos_x - 1][pos_y - 1];
    }
    // Borde superior
    else if (i == -1) {
      return *latice_[0][pos_y];
    }
    // Borde inferior
    else if (i == latice_.GetFilas()) {
      return *latice_[pos_x - 1][pos_y];
    }
    // Borde izquierdo
    else if (j == -1) {
      return *latice_[pos_x][0];
    }
    // Borde derecho
    else if (j == latice_.GetColumnas()) {
      return *latice_[pos_x][pos_y - 1];
    } else {
    return *latice_[pos_x][pos_y];
    }
  } else { //Frontera no border 0
    Celula* celulaEstadoCero = new Celula(Posicion(0,0),Estado(0));
    if (i < 0 || i >= latice_.GetFilas() || j < 0 || j >= latice_.GetColumnas()) {
        return *celulaEstadoCero;
    } else {
        return *latice_[i][j];
    }
  }    
}


bool Latice::Alrededor(int numero) {
  if (numero == 1) {
    for ( int i = 0; i < latice_[0].size(); i++) { // Borde de arriba osea la fila 0
      if ( latice_[0][i] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 2) {
    for (int i = 0; i < latice_.GetFilas();i++) { // columna 0
      if ( latice_[i][0] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 3) {
    for (int i = 0; i < latice_[0].size() ; i++) { // Fila n
      if ( latice_[latice_.GetFilas() - 1][i] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 4) {
    for (int i = 0; i < latice_.GetFilas(); i++) { // columna n
      if ( latice_[i][latice_.GetColumnas() - 1] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  }
}

Matriz Latice::GetMatriz() {
  return latice_;
}
Latice::Latice(std::string nombre, int frontera) {
  frontera_ = frontera;
  std::ifstream file(nombre);
  std::string cadena1;
  getline(file, cadena1);
  int filas = cadena1[0] - '0';
  int columnas = cadena1[2] - '0';
  if (frontera_ == 0 || frontera_ == 1) {
    filas += 2;
    columnas += 2;
  }
  numero_celulas_ = columnas * filas;
  latice_ = Matriz(filas, columnas, numero_celulas_);
  for (int i = 0; i < filas; i++) {
    std::string cadena;
    getline(file, cadena);
    for (int j = 0; j < columnas; j++) {
      int estado = 0;
      if (frontera_ == 2 || frontera_ == 3) {
        if (cadena[j] == 'X') {
          estado = 1;
        }
      } else if (frontera_ == 0 || frontera_ == 1) {
        if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
          estado = frontera_;
        } else if (cadena[j - 1] == 'X') {
          estado = 1;
        }
      }
      latice_[i][j] = new Celula(Posicion(i, j), Estado(estado));
    }
  }
}
