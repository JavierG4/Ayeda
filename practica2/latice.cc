#include "latice.h"
#include <iostream> // Add this line
#include <termios.h>
#include <unistd.h>
#include <limits>
#include <fstream>

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
  for (int i = latice_.GetIndiceInicial(); i < latice_.GetIndiceInicial() + latice_.GetFilas(); i++) {
    for (int j = latice_[0].GetIndiceInicial(); j < latice_[i].GetIndiceInicial() + latice_[i].size(); j++) {
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
        std::ofstream file("fichero.txt");
        for (int i = 0; i < latice_.GetFilas(); i++) {
          for (int j = 0; j < latice_[0].size(); j++) {
            file << latice_[i][j] -> GetEstado().GetEstado() << " ";
          }
          file << std::endl;
        }
      }
      //std::cout << latice_.GetFilas() << "-" << latice_.GetColumnas() << std::endl;
      for (int o = 0; o < veces ; o++) {
        int numero = 0;
        int col = latice_.GetColumnas() - 1;
        int fil = latice_.GetFilas() - 1;
        //std::cout << "col: " << col << " fil: " << fil << std::endl;
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
        std::ofstream file("fichero.txt");
        for (int i = 0; i < latice_.GetFilas(); i++) {
          for (int j = 0; j < latice_[0].size(); j++) {
            file << latice_[i][j] -> GetEstado().GetEstado() << " ";
          }
          file << std::endl;
        }
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
        std::ofstream file("fichero.txt");
        for (int i = latice_.GetIndiceInicial(); i < latice_.GetFilas() + latice_.GetIndiceInicial(); i++) {
          for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].size() + latice_[0].GetIndiceInicial(); j++) {
            file << latice_[i][j] -> GetEstado().GetEstado() << " ";
          }
          file << std::endl;
        }
      }
      std::cout << "veces: " << contador << " " << std::endl;
      for (int o = 0; o < veces ; o++) { 
        for (int i = latice_.GetIndiceInicial(); i < latice_.GetIndiceInicial() + latice_.GetFilas(); i++ ) {
          for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].GetIndiceInicial() + latice_[0].size() ; j++) { 
            //std::cout << "i" << i <<"j" << j << std::endl;
            latice_[i][j] -> SetEstadoSiguiente(latice_[i][j] -> NextState(*this)); 
          }
        }
        for (int i = latice_.GetIndiceInicial(); i < latice_.GetIndiceInicial() + latice_.GetFilas(); i++ ) {
          for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].GetIndiceInicial() + latice_[i].size() ; j++) { 
            latice_[i][j] -> UpdateState();
          }
        }
        std::cout << "Antes de comprobar" << std::endl;
        PrintLatice();
        //std::cout << "-" << std::endl;
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
  //std::cout << "alrededor 1" << flag1 << std::endl;
  int flag2 = Alrededor(2);
  //std::cout << "alrededor 2" << flag2 << std::endl;
  int flag3 = Alrededor(3);
  //std::cout << "alrededor 3" << flag3 << std::endl;
  int flag4 = Alrededor(4);
  //std::cout << "alrededor 4" << flag4 << std::endl;
  //std::cout << "Comprobando bordes" << std::endl;
  if (flag2) { //Columna izquierda
   // std::cout << "itam" << latice_[latice_.GetIndiceInicial()].size() << std::endl;
    //std::cout << "Alrededor 3" << std::endl;
    int inicial = latice_[latice_.GetIndiceInicial()].GetIndiceInicial() - 1;
    for (int i = 0; i < latice_.GetFilas(); i++) {
      //std::cout << "i: " << i << " ";
      Celula* cell = new Celula(Posicion(i + latice_.GetIndiceInicial(),inicial),Estado(0));
      latice_[i + latice_.GetIndiceInicial()].push_front(cell);
    }
    //PrintLatice();
    //std::cout << "itam" << latice_[latice_.GetIndiceInicial()].size() << std::endl;
  }
  if (flag4) { //Columna derecha
    //std::cout << "Alrededor 4" << std::endl;
    //std::cout << "itam1" << latice_[latice_.GetIndiceInicial()].size() << std::endl;
    int diferencia = latice_[0].GetIndiceInicial() + latice_[0].size();
    for (int i = 0; i < latice_.GetFilas(); i++) {
      //std::cout << "i1: " << i << " ";
      Celula* cell = new Celula(Posicion(i + latice_.GetIndiceInicial(),diferencia),Estado(0)); // cambio size/ i por i/size
      latice_[i + latice_.GetIndiceInicial()].push_back(cell);
    }
    //PrintLatice();
    //std::cout << "itam1" << latice_[latice_.GetIndiceInicial()].size() << std::endl;
  } 

  if (flag1) { //BORDE ARRIBA FILA
    //std::cout << "Alrededor 1" << std::endl;
    Myvector vector_aux(latice_[0].size());
    for (int i = 0; i < latice_[0].size(); i++) {
      //std::cout << "i2: " << i << " ";
      vector_aux[i] = new Celula(Posicion(latice_.GetIndiceInicial() - 1,i + latice_[0].GetIndiceInicial()),Estado(0));
    }
    vector_aux.SetIndiceInicial(latice_[0].GetIndiceInicial());
    latice_.Push_front(vector_aux);
    //PrintLatice();
  }
  if (flag3) { //FILA DE ABAJO
    //std::cout << "Alrededor 2" << std::endl;
    int diferencia = latice_.GetFilas() + latice_.GetIndiceInicial();
    Myvector vector_aux(latice_[0].size());
    for (int i = 0; i < latice_[0].size(); i++) {
      //std::cout << "i3: " << i << " ";
      vector_aux[i] = new Celula(Posicion(diferencia ,i + latice_[0].GetIndiceInicial()),Estado(0)); //latice_[0].size()
    }
    vector_aux.SetIndiceInicial(latice_[0].GetIndiceInicial());
    latice_.Push_back(vector_aux);
    //PrintLatice();
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
  //std::cout << latice_.GetIndiceInicial() << std::endl;
  //std::cout << latice_[0].GetIndiceInicial() << std::endl;
  for (int i = latice_.GetIndiceInicial(); i < latice_.GetFilas() + latice_.GetIndiceInicial(); i++) {
    for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].size() + latice_[0].GetIndiceInicial(); j++) {
      if (latice_[i][j] -> GetEstado().GetEstado() == 1) {
        std::cout << "X";
      } else {
        std::cout << "-";
      }
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
  for ( int i = latice_.GetIndiceInicial(); i < latice_.GetIndiceInicial() + latice_.GetFilas(); i++ ) { // Accedo a cada fila , es decir cada Myvector<celula*>
    for ( int j = latice_[i].GetIndiceInicial(); j < latice_[i].GetIndiceInicial() + latice_[i].size(); j++ ) { // Accedo a cada columna, es decir cada celula* y accedo a lo que apunta y le hago un get
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
    if (i < latice_.GetIndiceInicial() || i >= latice_.GetIndiceInicial() + latice_.GetFilas() || j < latice_[0].GetIndiceInicial() || j >= latice_[0].GetIndiceInicial() + latice_[0].size()) {
        return *celulaEstadoCero;
    } else {
      return *latice_[i][j];
    }
  }    
}

bool Latice::Alrededor(int numero) {
  int diferencia = latice_[0].size();
  if (numero == 1) {
    for ( int i = 0; i < diferencia; i++) { // Borde de arriba osea la fila 0
      if ( latice_[latice_.GetIndiceInicial()][i + latice_[latice_.GetIndiceInicial()].GetIndiceInicial()] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 2) {
    for (int i = 0; i < latice_.GetFilas();i++) { // columna 0
      //std::cout <<"i" << i <<"j: " << latice_[i][latice_[i].GetIndiceInicial()] ->GetPosicion().GetPosicionY()<< std::endl;
      //std::cout <<  latice_[i][latice_[i].GetIndiceInicial()] -> GetEstado().GetEstado() << std::endl;
      if ( latice_[i + latice_.GetIndiceInicial()][latice_[0].GetIndiceInicial()] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 3) {
    for (int i = 0; i < diferencia ; i++) { // Fila n
      if ( latice_[latice_.GetIndiceInicial() + latice_.GetFilas() -1][i + latice_[0].GetIndiceInicial()] -> GetEstado().GetEstado() == 1 ) {
        return true;
      }
    }
  } else if (numero == 4) {
    for (int i = 0; i < latice_.GetFilas(); i++) { // columna n
      if ( latice_[i + latice_.GetIndiceInicial()][latice_[0].GetIndiceInicial() + latice_[0].size() -1] -> GetEstado().GetEstado() == 1 ) {
        return true;      }
    }
  }
  return false;
}

Matriz Latice::GetMatriz() {
  return latice_;
}
Latice::Latice(std::string nombre,int frontera) {
  frontera_ = frontera;
  std::ifstream file(nombre);
  if (!file) {
    std::cerr << "No se pudo abrir el archivo " << nombre << std::endl;
    return;
  }
  int filas = 0;
  int columnas = 0;
  std::string cadena1;
  file >> filas;
  file >> columnas;
  getline(file,cadena1);
  if (frontera_ == 2 || frontera_ == 3 || frontera_ == 4) {
    numero_celulas_ = columnas * filas;
    latice_ = Matriz(filas, columnas, numero_celulas_);
    for ( int i = 0; i < filas; i++) {
      std::string cadena;
      //std::cout << i << "-" <<cadena.size() << std::endl;
      //std::cout << i << "_" << cadena << std::endl;
      getline(file,cadena);
      std::cout << i << "-" <<cadena.size() << std::endl;
      for (int j = 0; j < columnas; j++) {
        int estado = 0;
        if (cadena[j] == 'X') {
          //std::cout << "si" << i << " " << j << std::endl;
          estado = 1;
        }
        latice_[i][j] = new Celula(Posicion(i,j),Estado(estado));
      }
    }
  } else if (frontera_ == 0 || frontera_ == 1) {
    filas = filas + 2;
    columnas = columnas + 2;
    numero_celulas_ = columnas * filas;
    latice_ = Matriz(filas, columnas, numero_celulas_);
    for (int i = 1; i < filas - 1; i++) {
      std::string cadena;
      getline(file,cadena);
      for (int j = 1; j < columnas - 1; j++) {
        int estado = 0;
        if (cadena[j] == 'X') {
          estado = 1;
        }
        latice_[i][j] = new Celula(Posicion(i,j),Estado(estado));
      }
    }
    if ( frontera_ == 0 ) { 
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
    if ( frontera_ == 1 ) { 
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

std::ostream& operator<<(std::ostream& os, Latice& latice) {
  for (int i = 0; i < latice.latice_.GetFilas(); i++) {
    for (int j = 0; j < latice.latice_[0].size(); j++) {
      os << latice.latice_[i + latice.latice_.GetIndiceInicial()][j + latice.latice_[j].GetIndiceInicial()] -> GetEstado().GetEstado() << " ";
    }
    os << std::endl;
  }
  return os;
}


/*
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
      if (frontera_ == 2 || frontera_ == 3 || frontera_ == 4) {
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
*/
/* 
Latice::Latice(std::string nombre,int frontera) {
  frontera_ = frontera;
  std::ifstream file(nombre);
  int filas = 0;
  int columnas = 0;
  std::string cadena1;
  getline(file,cadena1);
  char aux = cadena1[0];
  char aux2 = cadena1[2];
  filas = aux - '0';
  columnas = aux2 - '0';
  if (frontera_ == 2 || frontera_ == 3 || frontera_ == 4) {
    numero_celulas_ = columnas * filas;
    latice_ = Matriz(filas, columnas, numero_celulas_);
    for ( int i = 0; i < filas; i++) {
      std::string cadena;
      //std::cout << i << "-" <<cadena.size() << std::endl;
      //std::cout << i << "_" << cadena << std::endl;
      getline(file,cadena);
      std::cout << i << "-" <<cadena.size() << std::endl;
      for (int j = 0; j < columnas; j++) {
        int estado = 0;
        if (cadena[j] == 'X') {
          //std::cout << "si" << i << " " << j << std::endl;
          estado = 1;
        }
        latice_[i][j] = new Celula(Posicion(i,j),Estado(estado));
      }
    }
  } else if (frontera_ == 0 || frontera_ == 1) {
    filas = filas + 2;
    columnas = columnas + 2;
    numero_celulas_ = columnas * filas;
    latice_ = Matriz(filas, columnas, numero_celulas_);
    for (int i = 1; i < filas - 1; i++) {
      std::string cadena;
      file >> cadena;
      for (int j = 1; j < columnas - 1; j++) {
        int estado = 0;
        if (cadena[j] == 'X') {
          estado = 1;
        }
        latice_[i][j] = new Celula(Posicion(i,j),Estado(estado));
      }
    }
    if ( frontera_ == 0 ) { 
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
    if ( frontera_ == 1 ) { 
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
*/
