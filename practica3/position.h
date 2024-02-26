#include <vector>
#include <stdexcept>

template <size_t N>
class Posicion {
 public:
   Posicion(const std::vector<int>& posiciones) {
     if (posiciones.size() != N) {
       throw std::invalid_argument("Número incorrecto de posiciones");
     }
     posiciones_ = posiciones;
   }

   Posicion() : posiciones_(N, 0) {}

   int GetPosicion(size_t dimension) {
     if (dimension >= N) {
       throw std::out_of_range("Dimensión fuera de rango");
     }
     return posiciones_[dimension];
   }

 private:
   std::vector<int> posiciones_;
};