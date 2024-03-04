#ifndef latice_h
#define latice_h

#include <iostream>

#include <stdlib.h>
#include <fstream>
#include <utility>
#include <set>
#include <vector>
//#include "myvector.h"
#include "celula.h"
//#include "matriz.h"
//#include "factorycell.h"
//#include "position.h"
//#include "estado.h"



class Celula;
/*
/**
 * @brief Clase que representa una red de células.
 */
/**
 * @class Latice
 * @brief Abstract base class representing a lattice.
 *
 * The Latice class provides an interface for working with lattices.
 * It defines pure virtual functions that must be implemented by derived classes.
 */
class Latice {
 public:
  /**
   * @brief Calculates the next generation of the lattice.
   *
   * This function is responsible for calculating the next generation of the lattice
   * based on the current state of the cells.
   */
  virtual void nextGeneration() = 0;

  /**
   * @brief Returns the population size of the lattice.
   *
   * This function returns the number of cells that are currently alive in the lattice.
   *
   * @return The population size of the lattice.
   */
  virtual std::size_t Population() = 0;

  /**
   * @brief Displays the lattice.
   *
   * This function displays the lattice by outputting its contents to the specified output stream.
   *
   * @param os The output stream to which the lattice will be displayed.
   * @return The output stream after displaying the lattice.
   */
  virtual std::ostream& display(std::ostream& os) = 0;

  /**
   * @brief Accesses the cell at the specified position.
   *
   * This function allows accessing the cell at the specified position in the lattice.
   *
   * @param pos The position of the cell to access.
   * @return A reference to the cell at the specified position.
   */
  virtual Celula& operator[](const Position& pos) = 0;

  /**
   * @brief Prints the instructions for using the lattice.
   *
   * This function prints the instructions for using the lattice to the standard output.
   */
  virtual void PrintInstrucciones() = 0;
};



#endif 