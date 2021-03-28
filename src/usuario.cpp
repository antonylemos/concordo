#include <string>

#include "../include/usuario.hpp"

using namespace std;

// Construtor padrão
Usuario::Usuario() {}

// Construtor sobrecarregado
Usuario::Usuario(int id, string email, string senha, string nome) {
  this->id = id;
  this->email = email;
  this->senha = senha;
  this->nome = nome;
}

// Destrutor
Usuario::~Usuario() {}

// Retorna o ID do usuário
int Usuario::getId() const {
  return id;
}

// Retorna o nome do usuário
string Usuario::getNome() const {
  return nome;
}

// Define o nome do usuário
void Usuario::setNome(string const nome) {
  this->nome = nome;
}

// Retorna o email do usuário
string Usuario::getEmail() const {
  return email;
}

// Define o email do usuário
void Usuario::setEmail(string const email) {
  this->email = email;
}

// Retorna a senha do usuário
string Usuario::getSenha() const {
  return senha;
}

// Define a senha do usuário
void Usuario::setSenha(string const senha) {
  this->senha = senha;
}
