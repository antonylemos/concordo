#ifndef CANAL_HPP
#define CANAL_HPP
#include <string>
#include <vector>

#include "mensagem.hpp"

using namespace std;

class Canal {
  protected:
    string nome;

  public:
    Canal();
    Canal(string const nome);
    ~Canal();

    virtual string getNome() const;
    virtual void setNome(string const nome);

    virtual vector<Mensagem> getMensagens() const = 0;
    virtual void sendMensagem(const Mensagem mensagem) = 0;
};

#endif
