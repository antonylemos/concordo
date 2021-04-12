#ifndef MENSAGEM_HPP
#define MENSAGEM_HPP
#include <string>

using namespace std;

class Mensagem {
  private:
    string dataHora;
    string conteudo;
    int enviadaPor;

  public:
    Mensagem();
    Mensagem(string dataHora, string conteudo, int enviadaPor);
    ~Mensagem();

    string getDataHora() const;
    void setDataHora(string const dataHora);

    string getConteudo() const;
    void setConteudo(string const conteudo);

    int getEnviadaPor() const;
    void setEnviadaPor(int const enviadaPor);
};

#endif
