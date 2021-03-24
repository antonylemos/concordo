#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include "sistema.hpp"
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

class Executor {
  private:
  Sistema * sistema;
  stringstream ss;
  bool sair = false;

  public:
  Executor(Sistema &sistema);

  void iniciar(istream &in, ostream &out);

  string processarLinha(string linha);
};

#endif