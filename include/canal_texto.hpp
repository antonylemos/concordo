#ifndef CANAL_TEXTO_HPP
#define CANAL_TEXTO_HPP
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
    CanalTexto(string const nome) : Canal(nome) {};
};

#endif
