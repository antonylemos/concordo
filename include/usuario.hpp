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
    Usuario();
    Usuario(int id, string nome, string email, string senha);
    ~Usuario();

    int getId() const;

    string getNome() const;
    void setNome(string const nome);

    string getEmail() const;
    void setEmail(string const email);

    string getSenha() const;
    void setSenha(string const senha);
};

#endif
