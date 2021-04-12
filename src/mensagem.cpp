#include <string>

#include "../include/mensagem.hpp"

using namespace std;

Mensagem::Mensagem() {}

Mensagem::Mensagem(string dataHora, string conteudo, int enviadaPor) {
  this->dataHora = dataHora;
  this->conteudo = conteudo;
  this->enviadaPor = enviadaPor;
}

Mensagem::~Mensagem() {}

string Mensagem::getDataHora() const {
  return dataHora;
}

void Mensagem::setDataHora(string const dataHora) {
  this->dataHora = dataHora;
}

string Mensagem::getConteudo() const {
  return conteudo;
}

void Mensagem::setConteudo(string const conteudo) {
  this->conteudo = conteudo;
}

int Mensagem::getEnviadaPor() const {
  return enviadaPor;
}

void Mensagem::setEnviadaPor(int const enviadaPor) {
  this->enviadaPor = enviadaPor;
}
