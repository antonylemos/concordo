#include <string>

#include "../include/servidor.hpp"

using namespace std;

// Construtor padrão
Servidor::Servidor() {}

// Construtor sobrecarregado
Servidor::Servidor(int usuarioDonoId, string nome) {
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
}

// Destrutor
Servidor::~Servidor() {}

// Retorna o ID do usuário dono do servidor
int Servidor::getUsuarioDonoId() const {
  return usuarioDonoId;
}

// Define o ID do usuário dono do servidor
void Servidor::setUsuarioDonoId(int const usuarioDonoId) {
  this->usuarioDonoId = usuarioDonoId;
}

// Retorna o nome do servidor
string Servidor::getNome() const {
  return nome;
}

// Define o nome do servidor
void Servidor::setNome(string const nome) {
  this->nome = nome;
}

// Retorna a descrição do servidor
string Servidor::getDescricao() const {
  return descricao;
}

// Define a descrição do servidor
void Servidor::setDescricao(string const descricao) {
  this->descricao = descricao;
}

// Retorna o código de convite do servidor
string Servidor::getCodigoConvite() const {
  return codigoConvite;
}

// Define o código de convite do servidor
void Servidor::setCodigoConvite(string const codigoConvite) {
  this->codigoConvite = codigoConvite;
}

// Retorna um vetor com os IDs dos participantes do servidor
vector<int> Servidor::getParticipantesIds(){
    return participantesIds;
}

// Insere um usuário na lista de participantes do servidor
bool Servidor::pushParticipante(int const participanteId) {
  for (int i = 0; i < participantesIds.size(); i++) {
    if (participantesIds[i] == participanteId) return false;
  }

  participantesIds.push_back(participanteId);

  return true;
}
