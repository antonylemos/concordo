#ifndef CANALVOZ_HPP
#define CANALVOZ_HPP
#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

using namespace std;

class CanalVoz : public Canal {
  private:
    Mensagem ultimaMensagem;

  public:
    CanalVoz();
    CanalVoz(string const nome);

    vector<Mensagem> getMensagens() const;
    virtual void sendMensagem(const Mensagem mensagem);
};

#endif
