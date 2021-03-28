#include <string>

#include "../include/servidor.hpp"

using namespace std;

Servidor::Servidor() {}

Servidor::Servidor(int usuarioDonoId, string nome) {
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
}

Servidor::~Servidor() {}

int Servidor::getUsuarioDonoId() const {
  return usuarioDonoId;
}

void Servidor::setUsuarioDonoId(int const usuarioDonoId) {
  this->usuarioDonoId = usuarioDonoId;
}

string Servidor::getNome() const {
  return nome;
}

void Servidor::setNome(string const nome) {
  this->nome = nome;
}

string Servidor::getDescricao() const {
  return descricao;
}

void Servidor::setDescricao(string const descricao) {
  this->descricao = descricao;
}

bool Servidor::pushParticipante(int const participanteId) {
  for (int i = 0; i < participantesIds.size(); i++) {
    if (participantesIds[i] == participanteId) return false;
  }

  participantesIds.push_back(participanteId);

  return true;
}
