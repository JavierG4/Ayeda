#include "latice1d.h"
#include "tools.h"

Latice1d::Latice1d(std::string name, FactoryCelula& factory){
  std::ifstream file(name);
  if (file.is_open()) {
    int n;
    file >> n;
    latice_.resize(n);
    std::string cadena;
    getline(file,cadena);
    getline(file,cadena);
    for (int i = 0; i < n; i++) {
      int estado = 0;
      if (cadena[i] == 'X') {
        estado = 1;
      }
      PositionDim<1> pos(1, i);
      latice_[i] = factory.createCelula(pos, Estado(estado));
      //std::cout << "Created cell at position " << (*latice_[i]->GetPosition())[0] << std::endl;
    }
  }
}

Latice1d::Latice1d(int n, FactoryCelula& factory) {
  latice_.resize(n);
  for (int i = 0; i < n; i++) {
    PositionDim<1> pos(1, i);
    latice_[i] = factory.createCelula(pos, Estado(0));
  }
  while(true) {
    std::cout << "Introduce la posicion de la celula viva (X para terminar)" << std::endl;
    std::string inputStr;
    std::cin >> inputStr;
    if(inputStr == "X") {
      std::cin.clear(); // Limpia el estado de error de std::cin
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada incorrecta
      break;
    }
    int input = std::stoi(inputStr);
    PositionDim<1> pos(1, input);
    latice_[input] = factory.createCelula(pos, Estado(1));
  }
}


void latice1d_open0::nextGeneration() {
  char input;
  //std::cout << "i" << std::endl;
  int contador = 1;  
  while(true) { 
    input = getch();
    if(input != ' ') {
      break;
    }
    for (int i = 0; i < latice_.size(); i++) {
      latice_[i]->SetEstadoSiguiente(latice_[i]->NextState(*this));
    }
    for (int i = 0; i < latice_.size(); i++) {
      latice_[i]->UpdateState();
    }
    display(std::cout) << " G(" << contador << ")" << std::endl;
    contador++;
  }
}

std::size_t latice1d_open0::Population() {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

Celula& latice1d_open0::operator[](const Position& pos ) {
  int i = pos[0];
  if( i < 0 || i >= latice_.size()) {
    PositionDim<1> pos(1, 0);
    return *(new CelulaAce110(pos, Estado(0)));
  } else {
    return *latice_[i];
  }
}

void latice1d_open1::nextGeneration() {
  char input;
  //std::cout << "i" << std::endl;
  int contador = 1;  
  while(true) { 
    input = getch();
    if(input != ' ') {
      break;
    }
    for (int i = 0; i < latice_.size(); i++) {
      latice_[i]->SetEstadoSiguiente(latice_[i]->NextState(*this));
    }
    for (int i = 0; i < latice_.size(); i++) {
      latice_[i]->UpdateState();
    }
    display(std::cout) << " G(" << contador << ")" << std::endl;
    contador++;
  }
}

std::size_t latice1d_open1::Population() {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

Celula& latice1d_open1::operator[](const Position& pos ) {
  int i = pos[0];
  if( i < 0 || i >= latice_.size()) {
    PositionDim<1> pos(1, 0);
    return *(new CelulaAce110(pos, Estado(1)));
  } else {
    return *latice_[i];
  }
}

void latice1d_periodic::nextGeneration() {
  char input;
  //std::cout << "i" << std::endl;
  int contador = 1;  
  while(true) { 
    input = getch();
    if(input != ' ') {
      break;
    }
    for (int i = 0; i < latice_.size(); i++) {
      latice_[i]->SetEstadoSiguiente(latice_[i]->NextState(*this));
    }
    for (int i = 0; i < latice_.size(); i++) {
      latice_[i]->UpdateState();
    }
    display(std::cout) << " G(" << contador << ")" << std::endl;
    contador++;
  }
}

std::size_t latice1d_periodic::Population() {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

Celula& latice1d_periodic::operator[](const Position& pos) {
  int i = pos[0];
  if(i < 0) {
    return *latice_[latice_.size() -1];
  } else if( i >= latice_.size()) {
    return *latice_[0];
  } else {
    return *latice_[i];
  }
}

std::ostream& latice1d_periodic::display(std::ostream& os) {
  for (int i = 0; i < latice_.size(); i++) {
    if(latice_[i]->GetEstado().GetEstado() == 1) {
      os << "X";
    } else {
      os << "-";
    }	
  }
  return os;
}

std::ostream& latice1d_open0::display(std::ostream& os) {
  for (int i = 0; i < latice_.size(); i++) {
    if(latice_[i]->GetEstado().GetEstado() == 1) {
      os << "X";
    } else {
      os << "-";
    }	
  }
  return os;
}

std::ostream& latice1d_open1::display(std::ostream& os) {
  for (int i = 0; i < latice_.size(); i++) {
    if(latice_[i]->GetEstado().GetEstado() == 1) {
      os << "X";
    } else {
      os << "-";
    }	
  }
  return os;
}

void Latice1d::PrintInstrucciones() {
  std::cout << "Instrucciones:" << std::endl;
  std::cout << "Pulse espacio para avanzar a la siguiente generacion" << std::endl;
  std::cout << "Pulse cualquier otra tecla para salir" << std::endl;
}