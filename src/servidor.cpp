#include <string>
#include <memory>
#include <algorithm>

#include "../include/servidor.hpp"
#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

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

vector<string> Servidor::getCanaisTexto() const {
  vector<string> listaCanais;

  for (auto itCanal = canais.begin(); itCanal != canais.end(); itCanal++) {
    if (dynamic_pointer_cast <CanalTexto> (*itCanal)) listaCanais.push_back((*itCanal)->getNome());
  }

  return listaCanais;
}

vector<string> Servidor::getCanaisVoz() const {
  vector<string> listaCanais;

  for (auto itCanal = canais.begin(); itCanal != canais.end(); itCanal++) {
    if (dynamic_pointer_cast <CanalVoz> (*itCanal)) listaCanais.push_back((*itCanal)->getNome());
  }

  return listaCanais;
}

vector <shared_ptr <Canal>> Servidor::getCanais() const {
  return canais;
}

bool Servidor::createCanal(shared_ptr <Canal> canal) {
  if (canal == nullptr) return false;

  canais.push_back(canal);

  return true;
}

// Insere um usuário na lista de participantes do servidor
bool Servidor::pushParticipante(int const participanteId) {
  for (int i = 0; i < participantesIds.size(); i++) {
    if (participantesIds[i] == participanteId) return false;
  }

  participantesIds.push_back(participanteId);

  return true;
}

vector<Mensagem> Servidor::getMensagens(const string nomeCanal) {
  auto findCanal = find_if(canais.begin(), canais.end(), [nomeCanal](std::shared_ptr <Canal> canal) {
    return canal->getNome() == nomeCanal;
  });

  return (*findCanal)->getMensagens();
}

void Servidor::sendMensagem(const string nomeCanal, const Mensagem mensagem) {
  auto findCanal = find_if(canais.begin(), canais.end(), [nomeCanal](std::shared_ptr <Canal> canal) {
    return canal->getNome() == nomeCanal;
  });

  (*findCanal)->sendMensagem(mensagem);
}
