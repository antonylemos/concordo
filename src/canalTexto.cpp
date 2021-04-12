#include <string>

#include "../include/canal.hpp"
#include "../include/canalTexto.hpp"
#include "../include/mensagem.hpp"

using namespace std;

CanalTexto::CanalTexto() {}

CanalTexto::CanalTexto(string const nome) : Canal(nome) {}

vector<Mensagem> CanalTexto::getMensagens() const {
  return mensagens;
}

void CanalTexto::sendMensagem(const Mensagem mensagem) {
  mensagens.push_back(mensagem);
}
