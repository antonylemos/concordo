#ifndef CANALTEXTO_HPP
#define CANALTEXTO_HPP
#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

using namespace std;

class CanalTexto : public Canal {
  private:
    vector<Mensagem> mensagens;

  public:
    CanalTexto();
    CanalTexto(string const nome);

    vector<Mensagem> getMensagens() const;
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
