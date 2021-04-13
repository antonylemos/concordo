#ifndef CANALTEXTO_HPP
#define CANALTEXTO_HPP
#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

using namespace std;

class CanalTexto : public Canal {
  // Atributos da classe
  private:
    vector<Mensagem> mensagens;

  // Métodos da classe
  public:
    // Construtor
    CanalTexto();
    // Construtor sobrecarregado
    CanalTexto(string const nome);

    // Retorna um vetor de mensagens
    vector<Mensagem> getMensagens() const;
    // Adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
