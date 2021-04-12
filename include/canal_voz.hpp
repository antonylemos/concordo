#ifndef CANAL_VOZ_HPP
#define CANAL_VOZ_HPP
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
    CanalVoz(string const nome) : Canal(nome) {};
};

#endif
