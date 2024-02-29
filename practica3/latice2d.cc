#include "latice2d.h"
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

Latice2d::Latice2d(std::string tipo, FactoryCelula& factory) {
  std::ifstream file(tipo);
  if (!file) {
    std::cerr << "No se pudo abrir el archivo " << tipo << std::endl;
    return;
  }
  int filas = 0;
  int columnas = 0;
  std::string cadena1;
  file >> filas;
  file >> columnas;
  getline(file,cadena1);
  latice_ = Matriz(filas, columnas, filas*columnas);
  for ( int i = 0; i < filas; i++) {
    std::string cadena;
      //std::cout << i << "-" <<cadena.size() << std::endl;
      //std::cout << i << "_" << cadena << std::endl;
    getline(file,cadena);
    //std::cout << i << "-" <<cadena.size() << std::endl;
    for (int j = 0; j < columnas; j++) {
      int estado = 0;
      if (cadena[j] == 'X') {
          //std::cout << "si" << i << " " << j << std::endl;
        estado = 1;
      }
      PositionDim<2> pos(2,i,j);
      latice_[i][j] = factory.createCelula(pos,Estado(estado));
    }
  }
}

void latice2d_reflective::nextGeneration() {
    std::cout << "Entro refle" << std::endl;
  char input;
  bool flagc = 0;
  int contador = 0;
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
    for ( int i = 0; i < veces; i++) { 
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->SetEstadoSiguiente(latice_[i][j]->NextState(*this));
        }
      }
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->UpdateState();
        }
      }
      if (flagc == 0) { 
        std::cout << "G ( " << contador << " ) " << std::endl;
        display(std::cout);
        contador++;
      } else if (flagc == 1) {
        std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
          //PrintLatice();
        contador++;
      }
    }
  }
}

std::size_t latice2d_reflective::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_reflective::operator[](const Position& pos) {
  int i = pos[0];
  int j = pos[1];
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
}

void latice2d_periodic::nextGeneration() {
    std::cout << "Entro p" << std::endl;
  char input;
  bool flagc = 0;
  int contador = 0;
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
    for ( int i = 0; i < veces; i++) { 
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->SetEstadoSiguiente(latice_[i][j]->NextState(*this));
        }
      }
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->UpdateState();
        }
      }
      if (flagc == 0) { 
        std::cout << "G ( " << contador << " ) " << std::endl;
        display(std::cout);
        contador++;
      } else if (flagc == 1) {
        std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
          //PrintLatice();
        contador++;
      }
    }
  }
}

std::size_t latice2d_periodic::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_periodic::operator[](const Position& pos) {
  int i = pos[0];
  int j = pos[1];
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
}

void latice2d_open0::nextGeneration() {
  std::cout << "Entro 0" << std::endl;
  char input;
  bool flagc = 0;
  int contador = 0;
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
    for ( int i = 0; i < veces; i++) { 
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          int x = latice_[i][j]->NextState(*this);
          //std::cout << x << " ";
          latice_[i][j]->SetEstadoSiguiente(x);
        }
      }
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->UpdateState();
        }
      }
      if (flagc == 0) { 
        std::cout << "G ( " << contador << " ) " << std::endl;
        display(std::cout);
        contador++;
      } else if (flagc == 1) {
        std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
          //PrintLatice();
        contador++;
      }
    }
  }
}

std::size_t latice2d_open0::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_open0::operator[](const Position& pos) {
  int x = pos[0];
  int y = pos[1];
  if(x < 0 || y < 0 || x >= latice_.GetFilas() || y >= latice_[0].size()) {
    PositionDim<2> pos(2,0,0);
    Celula* celulaEstadoUno = new CelulaLife23_3(pos, Estado(1));
    return *celulaEstadoUno;
  }
  return *latice_[pos[0]][pos[1]];
}

void latice2d_open1::nextGeneration() {
  std::cout << "Entro 1" << std::endl;
  char input;
  bool flagc = 0;
  int contador = 0;
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
    for ( int i = 0; i < veces; i++) { 
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->SetEstadoSiguiente(latice_[i][j]->NextState(*this));
        }
      }
      for (int i = 0; i < latice_.GetFilas(); i++) {
        for (int j = 0; j < latice_[i].size(); j++) {
          latice_[i][j]->UpdateState();
        }
      }
      if (flagc == 0) { 
        std::cout << "G ( " << contador << " ) " << std::endl;
        display(std::cout);
        contador++;
      } else if (flagc == 1) {
        std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
          //PrintLatice();
        contador++;
      }
    }
  }
}

std::size_t latice2d_open1::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_open1::operator[](const Position& pos) {
  if(pos[0] < 0 || pos[1] < 0 || pos[0] >= latice_.GetFilas() || pos[1] >= latice_[0].size()) {
    PositionDim<2> pos(2,0,0);
    Celula* celulaEstadoUno = new CelulaLife23_3(pos, Estado(1));
    return *celulaEstadoUno;
  }
  return *latice_[pos[0]][pos[1]];
}

std::ostream& latice2d_open1::display(std::ostream& os) {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      os << latice_[i][j]->GetEstado().GetEstado() << " ";
    }
    os << std::endl;
  }
  return os;
}

std::ostream& latice2d_open0::display(std::ostream& os) {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      os << latice_[i][j]->GetEstado().GetEstado() << " ";
    }
    os << std::endl;
  }
  return os;
}

std::ostream& latice2d_periodic::display(std::ostream& os) {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      os << latice_[i][j]->GetEstado().GetEstado() << " ";
    }
    os << std::endl;
  }
  return os;
}

std::ostream& latice2d_reflective::display(std::ostream& os) {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      os << latice_[i][j]->GetEstado().GetEstado() << " ";
    }
    os << std::endl;
  }
  return os;
}

void latice2d_noborder::nextGeneration() {
  bool flagc = false;
  int contador = 1;
  char input;
  while (true) {
    int veces = 0;
    input = getch();
    if (input == 'x') {
      break;
    } else if (input == 'n') {
      veces = 1;
    } else if (input == 'L') {
      veces = 5;
    } else if (input == 'c') {
      flagc = true;
    } else if (input == 's') { // guardar en fichero
      std::ofstream file("fichero.txt");
      for (int i = latice_.GetIndiceInicial(); i < latice_.GetFilas() + latice_.GetIndiceInicial(); i++) {
        for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].size() + latice_[0].GetIndiceInicial(); j++) {
          file << latice_[i][j]->GetEstado().GetEstado() << " ";
        }
        file << std::endl;
      }
    }
    std::cout << "veces: " << contador << " " << std::endl;
    for (int o = 0; o < veces; o++) {
      for (int i = latice_.GetIndiceInicial(); i < latice_.GetIndiceInicial() + latice_.GetFilas(); i++) {
        for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].GetIndiceInicial() + latice_[0].size(); j++) {
          latice_[i][j]->SetEstadoSiguiente(latice_[i][j]->NextState(*this));
        }
      }
      for (int i = latice_.GetIndiceInicial(); i < latice_.GetIndiceInicial() + latice_.GetFilas(); i++) {
        for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].GetIndiceInicial() + latice_[i].size(); j++) {
          latice_[i][j]->UpdateState();
        }
      }
      //std::cout << "-" << std::endl;
      Comprobar();
      if (flagc == false) {
        std::cout << "G ( " << contador << " ) " << std::endl;
        display(std::cout);
        contador++;
      } else if (flagc == true) {
        std::cout << "Population: " << Population() << " G( " << contador << " )" << std::endl;
        //PrintLatice();
        contador++;
      }
    }
  }
}


void latice2d_noborder::Comprobar() {
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
      PositionDim<2> pos(2,i + latice_.GetIndiceInicial() ,inicial);
      Celula* cell = factory.createCelula(pos,Estado(0));
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
      PositionDim<2> pos(2,i + latice_.GetIndiceInicial(),diferencia);
      Celula* cell = factory.createCelula(pos,Estado(0)); // cambio size/ i por i/size
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
      PositionDim<2> pos(2,latice_.GetIndiceInicial() - 1,i + latice_[0].GetIndiceInicial());
      vector_aux[i] = factory.createCelula(pos,Estado(0));
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
      PositionDim<2> pos(2,diferencia ,i + latice_[0].GetIndiceInicial());
      vector_aux[i] = factory.createCelula(pos,Estado(0)); //latice_[0].size()
    }
    vector_aux.SetIndiceInicial(latice_[0].GetIndiceInicial());
    latice_.Push_back(vector_aux);
    //PrintLatice();
  }
}

bool latice2d_noborder::Alrededor(int numero) {
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
        return true;      
      }
    }
  }
  return false;
}


std::size_t latice2d_noborder::Population(){
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
Celula& latice2d_noborder::operator[](const Position& pos1){
  int i = pos1[0];
  int j = pos1[1];
  PositionDim<2> pos(2,0,0);
  Celula* celulaEstadoCero = factory.createCelula(pos,Estado(0));
  if (i < latice_.GetIndiceInicial() || i >= latice_.GetIndiceInicial() + latice_.GetFilas() || j < latice_[0].GetIndiceInicial() || j >= latice_[0].GetIndiceInicial() + latice_[0].size()) {
    return *celulaEstadoCero;
  } else {
    return *latice_[i][j];
  }
}

std::ostream& latice2d_noborder::display(std::ostream& os) {
  for (int i = latice_.GetIndiceInicial(); i < latice_.GetFilas() + latice_.GetIndiceInicial(); i++) {
    for (int j = latice_[0].GetIndiceInicial(); j < latice_[0].size() + latice_[0].GetIndiceInicial(); j++) {
      if (latice_[i][j] -> GetEstado().GetEstado() == 1) {
        os << "X";
      } else {
        os << "-";
      }
    }
    os << std::endl;
  }
  return os;
}