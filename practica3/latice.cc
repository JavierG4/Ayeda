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

/*
Latice::Latice(std::string, const FactoryCelula&){
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
}
*/