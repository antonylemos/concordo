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
    void carregarServidores();

  public:
    Sistema();
    ~Sistema();

    string quit();
    /**
     * Cria um novo usuário.
     * @param email
     * @param senha
     * @param nome
    */
    string create_user (const string email, const string senha, const string nome);
    /**
     * Conecta um usuário.
     * @param email
     * @param senha
    */
    string login(const string email, const string senha);
    /**
     * Desconecta um usuário
    */
    string disconnect();
    /**
     * Cria um novo servidor.
     * @param nome
    */
    string create_server(const string nome);
    /**
     * Altera a descrição de um servidor.
     * @param nome
     * @param descricao
    */
    string set_server_desc(const string nome, const string descricao);
    /**
     * Altera o código de convite de um servidor.
     * @param nome
     * @param codigo
    */
    string set_server_invite_code(const string nome, const string codigo);
    /**
     * Lista servidores.
     * @return Lista de servidores
    */
    string list_servers();
    /**
     * Remove um servidor.
     * @param nome
    */
    string remove_server(const string nome);
    /**
     * Entra em um servidor.
     * @param nome
     * @param codigo
    */
    string enter_server(const string nome, const string codigo);
    /**
     * Sai de um servidor.
    */
    string leave_server();
    /**
     * Lista participantes de um servidor.
     * @return Lista de participantes
    */
    string list_participants();
    /**
     * Lista canais de um servidor.
     * @return Lista de canais
    */
    string list_channels();
    /**
     * Cria um novo canal em um servidor.
     * @param nome
     * @param tipo
    */
    string create_channel(const string nome, const string tipo);
    /**
     * Entra em um canal.
     * @param nome
     * @param tipo
    */
    string enter_channel(const string nome, const string tipo);
    /**
     * Sai de um canal.
    */
    string leave_channel();
    /**
     * Envia mensagem em um canal.
     * @param mensagem
    */
    string send_message(const string mensagem);
    /**
     * Lista as mensagens de um canal.
     * @return Lista de mensagens
    */
    string list_messages();

    /**
     * Salva dados da aplicação.
    */
    void salvar();
    /**
     * Carrega dados da aplicação.
    */
    void carregar();
};

#endif
