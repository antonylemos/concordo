#include <iostream>
#include <sstream>
#include <algorithm>

#include "../include/sistema.hpp"

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
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nome.empty()) return "Não é possível criar um servidor sem nome.";

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) return "Servidor com esse nome já existe.";
  }

  Servidor newServidor(usuarioLogadoId, nome);

  newServidor.pushParticipante(usuarioLogadoId);
  servidores.push_back(newServidor);

  return "Servidor criado.";
}

string Sistema::set_server_desc(const string nome, const string descricao) {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  if (!isServidor) return "Servidor \'" + nome + "\' não existe.";

  if (findServidor.getUsuarioDonoId() != usuarioLogadoId)
    return "Você não pode alterar a descrição de um servidor que não foi criado por você.";

  findServidor.setDescricao(descricao);

  return "Descrição do servidor \'" + nome + "\' modificada.";
}

string Sistema::set_server_invite_code(const string nome, const string codigo) {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  if (!isServidor) return "Servidor \'" + nome + "\' não existe.";

  if (findServidor.getUsuarioDonoId() != usuarioLogadoId)
    return "Você não pode alterar o código de convite de um servidor que não foi criado por você.";

  findServidor.setCodigoConvite(codigo);

  if (!codigo.empty()) return "Código de convite do servidor \'" + nome + "\' modificado.";
  else return "Código de convite do servidor \'" + nome + "\' removido.";
}

string Sistema::list_servers() {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (servidores.empty()) return "Não há servidores cadastrados.";

  string listaServidores = "";

  for (int i = 0; i < servidores.size(); i++) {
    listaServidores += servidores[i].getNome() + "\n";
  }

  return listaServidores;
}

string Sistema::remove_server(const string nome) {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  vector<Servidor>::iterator findServidor;

  findServidor = find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
    return servidor.getNome() == nome;
  });

  if (findServidor == servidores.end()) return "Servidor \'" + nome + "\' não encontrado.";

  if (findServidor->getUsuarioDonoId() != usuarioLogadoId)
    return "Você não é o dono do servidor \'" + nome + "\'.";

  if(findServidor->getNome() == nomeServidorConectado) leave_server();

  servidores.erase(findServidor);

  return "Servidor \'" + nome + "\' removido.";
}

string Sistema::enter_server(const string nome, const string codigo) {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  if (!isServidor) return "Servidor \'" + nome + "\' não existe.";

  if (findServidor.getUsuarioDonoId() == usuarioLogadoId) {
    findServidor.pushParticipante(usuarioLogadoId);
    return "Entrou no servidor com sucesso.";
  } else if (findServidor.getCodigoConvite().empty()) {
    findServidor.pushParticipante(usuarioLogadoId);
    return "Entrou no servidor com sucesso.";
  } else if (findServidor.getCodigoConvite() == codigo) {
    findServidor.pushParticipante(usuarioLogadoId);
    return "Entrou no servidor com sucesso.";
  } else if (!findServidor.getCodigoConvite().empty() && codigo.empty()) {
    return "Servidor requer código de convite";
  } else {
    return "Código de convite incorreto";
  }
}

string Sistema::leave_server() {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a nenhum servidor.";

  nomeServidorConectado = "";

  return "Saindo do servidor \'" + nomeServidorConectado + "\'.";
}

string Sistema::list_participants() {
  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  Servidor findServidor;
  bool isServidor = false;

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nomeServidorConectado) {
      findServidor = servidores[i];
      isServidor = true;
    };
  }

  string listaParticipantes = "";
  vector<int> listaIds = findServidor.getParticipantesIds();

  for (int i = 0; i < usuarios.size(); i++) {
    for (int j = 0; j < listaIds.size(); j++) {
      if (usuarios[i].getId() == listaIds[j]) listaParticipantes += usuarios[i].getNome() + "\n";
    }
  }

  return listaParticipantes;
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
