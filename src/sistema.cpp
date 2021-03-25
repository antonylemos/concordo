#include "../include/sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Sistema::Sistema() {
  this->usuarioLogadoId = 0; // se 0: não logado, caso contrário guarda o id do usuário logado
  this->nomeServidorConectado = "";
  this->nomeCanalConectado = "";
}

Sistema::~Sistema() {}

string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  if (usuarioLogadoId) return "Não foi possível realizar o cadastro.\nO usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " encontra-se logado!";

  for (int i = 0; i < usuarios.size(); i++) {
    if (usuarios[i].getEmail() == email) return "Usuário já existe.";
  }

  Usuario newUsuario((int)(usuarios.size() + 1), email, senha, nome);
  usuarios.push_back(newUsuario);

  return "Usuário criado!";
}

string Sistema::login(const string email, const string senha) {
  if (!usuarioLogadoId) {
    for (int i = 0; i < usuarios.size(); i++) {
      if (usuarios[i].getEmail() == email) {
        if (usuarios[i].getSenha() == senha) {
          usuarioLogadoId = usuarios[i].getId();

          return "Login realizado como " + usuarios[i].getEmail() + "!";
        }
      }

      return "Email ou senha incorretos. Verifique e tente novamente!";
    }
  }

  return "Não foi possível realizar o login.\nO usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " encontra-se logado!";
}

string Sistema::disconnect() {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  int usuarioLogadoIdAnterior = usuarioLogadoId;
  usuarioLogadoId = 0;

  return "Desconectando usuário " + usuarios[usuarioLogadoIdAnterior - 1].getEmail() + ".";
}

string Sistema::create_server(const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers() {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server() {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants() {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels() {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(const string nome, const string tipo) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel() {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages() {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
