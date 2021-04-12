#include <string>

#include "../include/canal.hpp"
#include "../include/canalVoz.hpp"
#include "../include/mensagem.hpp"

using namespace std;

CanalVoz::CanalVoz() {}

CanalVoz::CanalVoz(string const nome) : Canal(nome) {}

vector<Mensagem> CanalVoz::getMensagens() const {
  vector<Mensagem> mensagens;

  if (!ultimaMensagem.getConteudo().empty()) mensagens.push_back(ultimaMensagem);

  return mensagens;
}

void CanalVoz::sendMensagem(const Mensagem mensagem) {
  ultimaMensagem.setConteudo(mensagem.getConteudo());
  ultimaMensagem.setDataHora(mensagem.getDataHora());
  ultimaMensagem.setEnviadaPor(mensagem.getEnviadaPor());
}
