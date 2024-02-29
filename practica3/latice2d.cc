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
  if (i == -1 && j == - 1) {
    return *latice_[0][0];
  } 
    //Arriba derecha
  else if (i == -1 && j == latice_.GetColumnas()) {
    return *latice_ [0][j - 1];
  }
    // Esquina inferior izquierda
  else if (i == latice_.GetFilas() && j == -1) {
    return *latice_[i- 1][0];
  }
    // Esquina inferior derecha
  else if (i == latice_.GetFilas()  && j == latice_.GetColumnas()) {
    return *latice_[i - 1][j - 1];
  }
    // Borde superior
  else if (i == -1) {
    return *latice_[0][j];
  }
    // Borde inferior
  else if (i == latice_.GetFilas()) {
    return *latice_[i - 1][j];
  }
    // Borde izquierdo
  else if (j == -1) {
    return *latice_[i][0];
  }
    // Borde derecho
  else if (j == latice_.GetColumnas()) {
    return *latice_[i][j - 1];
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
    for ( int i = 0; i <latice_.GetFilas(); i++) {
      for (int j = 0; j < latice_[0].size(); j++) {
        if (latice_[i][j]->GetEstado().GetEstado() == 0) {
          return *latice_[i][j];
        }
      }
    }
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
    for ( int i = 0; i <latice_.GetFilas(); i++) {
      for (int j = 0; j < latice_[0].size(); j++) {
        if (latice_[i][j]->GetEstado().GetEstado() == 1) {
          return *latice_[i][j];
        }
      }
    }
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

