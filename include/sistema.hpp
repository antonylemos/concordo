#ifndef SISTEMA_HPP
#define SISTEMA_HPP
#include <vector>
#include <string>
#include <iostream>

#include "usuario.hpp"
#include "servidor.hpp"

using namespace std;

// Sistema deve concentrar todas as operações do Concordo
class Sistema {
  private:
    vector <Servidor> servidores;
    vector <Usuario> usuarios;
    int usuarioLogadoId;
    string nomeServidorConectado;
    string nomeCanalConectado;

    void salvarUsuarios();
    void salvarServidores();

    void carregarUsuarios();

  public:
    Sistema();
    ~Sistema();

    string quit();
    string create_user (const string email, const string senha, const string nome);
    string login(const string email, const string senha);
    string disconnect();
    string create_server(const string nome);
    string set_server_desc(const string nome, const string descricao);
    string set_server_invite_code(const string nome, const string codigo);
    string list_servers();
    string remove_server(const string nome);
    string enter_server(const string nome, const string codigo);
    string leave_server();
    string list_participants();
    string list_channels();
    string create_channel(const string nome, const string tipo);
    string enter_channel(const string nome, const string tipo);
    string leave_channel();
    string send_message(const string mensagem);
    string list_messages();

    void salvar();
    void carregar();
};

#endif
