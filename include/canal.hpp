#ifndef CANAL_HPP
#define CANAL_HPP
#include <string>
#include <vector>

#include "mensagem.hpp"

using namespace std;

class Canal {
  // Atributos da classe
  protected:
    string nome;
    string tipo;

  // Métodos da classe
  public:
    // Construtor
    Canal();
    // Construtor sobrecarregado
    Canal(string const nome, string const tipo);
    // Destrutor
    ~Canal();

    // Retorna o nome do canal
    virtual string getNome() const;
    // Altera o nome do canal
    virtual void setNome(string const nome);
    // Retorna o tipo do canal
    virtual string getTipo() const;
    // Altera o tipo do canal
    virtual void setTipo(string const tipo);

    // Retorna um vetor de mensagens
    virtual vector<Mensagem> getMensagens() const = 0;
    // Adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem) = 0;
};

#endif
