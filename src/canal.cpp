#include <string>

#include "../include/canal.hpp"

using namespace std;

Canal::Canal() {}

Canal::Canal(string const nome) {
  this->nome = nome;
}

Canal::~Canal() {}

string Canal::getNome() const {
  return nome;
}

void Canal::setNome(string const nome) {
  this->nome = nome;
}
