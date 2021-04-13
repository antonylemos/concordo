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

  // Métodos da classe
  public:
    // Construtor
    Canal();
    // Construtor sobrecarregado
    Canal(string const nome);
    // Destrutor
    ~Canal();

    // Retorna o nome do canal
    virtual string getNome() const;
    // Altera o nome do canal
    virtual void setNome(string const nome);

    // Retorna um vetor de mensagens
    virtual vector<Mensagem> getMensagens() const = 0;
    // Adiciona mensagem ao vetor de mensagens
    virtual void sendMensagem(const Mensagem mensagem) = 0;
};

#endif
