#include <string>

#include "../include/canal.hpp"

using namespace std;

Canal::Canal() {}

Canal::Canal(string const nome, string const tipo) {
  this->nome = nome;
  this->tipo = tipo;
}

Canal::~Canal() {}

string Canal::getNome() const {
  return nome;
}

void Canal::setNome(string const nome) {
  this->nome = nome;
}

string Canal::getTipo() const {
  return tipo;
}

void Canal::setTipo(string const tipo) {
  this->tipo = tipo;
}
