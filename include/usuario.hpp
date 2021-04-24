#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

using namespace std;

class Usuario {
  // Atributos da classe
  private:
    int id;
    string email;
    string senha;
    string nome;

  // Métodos da classe
  public:
    // Construtor
    Usuario();
    // Construtor sobrecarregado
    Usuario(int id, string nome, string email, string senha);
    // Destrutor
    ~Usuario();

    // Retorna o ID do usuário
    int getId() const;

    // Retorna o nome do usuário
    string getNome() const;
    // Altera o nome do usuário
    void setNome(string const nome);

    // Retorna o email do usuário
    string getEmail() const;
    // Altera o email do usuário
    void setEmail(string const email);

    // Retorna a senha do usuário
    string getSenha() const;
    // Altera a senha do usuário
    void setSenha(string const senha);
};

#endif
