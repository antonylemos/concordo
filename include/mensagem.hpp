#ifndef MENSAGEM_HPP
#define MENSAGEM_HPP
#include <string>

using namespace std;

class Mensagem {
  // Atributos da classe
  private:
    string dataHora;
    string conteudo;
    int enviadaPor;

  // Métodos da classe
  public:
    // Construtor
    Mensagem();
    // Construtor sobrecarregado
    Mensagem(string dataHora, string conteudo, int enviadaPor);
    // Destrutor
    ~Mensagem();

    // Retorna o atributo dataHora
    string getDataHora() const;
    // Altera o atributo dataHora
    void setDataHora(string const dataHora);

    // Retorna o atributo conteudo
    string getConteudo() const;
    // Altera o atributo conteudo
    void setConteudo(string const conteudo);

    // Retorna o atributo enviadaPor
    int getEnviadaPor() const;
    // Altera o atributo enviadaPor
    void setEnviadaPor(int const enviadaPor);
};

#endif
