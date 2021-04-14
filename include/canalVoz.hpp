#ifndef CANALVOZ_HPP
#define CANALVOZ_HPP
#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

using namespace std;

class CanalVoz : public Canal {
  // Atributos da classe
  private:
    Mensagem ultimaMensagem;

  // Métodos da classe
  public:
    // Construtor
    CanalVoz();
    // Construtor sobrecarregado
    CanalVoz(string const nome, string const tipo);

    // Retorna um vetor de mensagens
    vector<Mensagem> getMensagens() const;
    // Adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
