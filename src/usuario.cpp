#include <string>

#include "../include/usuario.hpp"

using namespace std;

Usuario::Usuario() {}

Usuario::Usuario(int id, string email, string senha, string nome) {
  this->id = id;
  this->email = email;
  this->senha = senha;
  this->nome = nome;
}

Usuario::~Usuario() {}

int Usuario::getId() const {
  return id;
}

string Usuario::getNome() const {
  return nome;
}

void Usuario::setNome(string const nome) {
  this->nome = nome;
}

string Usuario::getEmail() const {
  return email;
}

void Usuario::setEmail(string const email) {
  this->email = email;
}

string Usuario::getSenha() const {
  return senha;
}

void Usuario::setSenha(string const senha) {
  this->senha = senha;
}
