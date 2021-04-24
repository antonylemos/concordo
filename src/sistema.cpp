#include <iostream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <fstream>

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
  carregar();

  if (usuarioLogadoId) return "Não foi possível realizar o cadastro.\nO usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " encontra-se logado!";

  if (email.empty() && senha.empty() && nome.empty()) return "Preencha todos os campos para cadastrar um usuário";

  for (int i = 0; i < usuarios.size(); i++) {
    if (usuarios[i].getEmail() == email) return "Usuário já existe.";
  }

  Usuario newUsuario((int)(usuarios.size() + 1), email, senha, nome);
  usuarios.push_back(newUsuario);

  salvar();

  return "Usuário criado!";
}

string Sistema::login(const string email, const string senha) {
  carregar();

  if (!usuarioLogadoId) {
    for (int i = 0; i < usuarios.size(); i++) {
      if (usuarios[i].getEmail() == email && usuarios[i].getSenha() == senha) {
        usuarioLogadoId = usuarios[i].getId();

        return "Login realizado como " + usuarios[i].getEmail() + "!";
      }
    }

    return "Email ou senha incorretos. Verifique e tente novamente!";
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
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nome.empty()) return "Não é possível criar um servidor sem nome.";

  for (int i = 0; i < servidores.size(); i++) {
    if (servidores[i].getNome() == nome) return "Servidor com esse nome já existe.";
  }

  Servidor newServidor(usuarioLogadoId, nome);

  newServidor.pushParticipante(usuarioLogadoId);
  servidores.push_back(newServidor);

  nomeServidorConectado = nome;

  salvar();

  return "Servidor criado.";
}

string Sistema::set_server_desc(const string nome, const string descricao) {
  carregar();

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

  salvar();

  return "Descrição do servidor \'" + nome + "\' modificada.";
}

string Sistema::set_server_invite_code(const string nome, const string codigo) {
  carregar();

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

  salvar();

  if (!codigo.empty()) return "Código de convite do servidor \'" + nome + "\' modificado.";
  else return "Código de convite do servidor \'" + nome + "\' removido.";
}

string Sistema::list_servers() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (servidores.empty()) return "Não há servidores cadastrados.";

  string listaServidores = "";

  for (int i = 0; i < servidores.size(); i++) {
    listaServidores += servidores[i].getNome() + "\n";
  }

  return listaServidores;
}

string Sistema::remove_server(const string nome) {
  carregar();

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

  salvar();

  return "Servidor \'" + nome + "\' removido.";
}

string Sistema::enter_server(const string nome, const string codigo) {
  carregar();

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
    salvar();
    nomeServidorConectado = nome;
    return "Entrou no servidor com sucesso.";
  } else if (findServidor.getCodigoConvite().empty()) {
    findServidor.pushParticipante(usuarioLogadoId);
    salvar();
    nomeServidorConectado = nome;
    return "Entrou no servidor com sucesso.";
  } else if (findServidor.getCodigoConvite() == codigo) {
    findServidor.pushParticipante(usuarioLogadoId);
    salvar();
    nomeServidorConectado = nome;
    return "Entrou no servidor com sucesso.";
  } else if (!findServidor.getCodigoConvite().empty() && codigo.empty()) {
    return "Servidor requer código de convite";
  } else {
    return "Código de convite incorreto";
  }
}

string Sistema::leave_server() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a nenhum servidor.";

  string nomeServidor = nomeServidorConectado;

  nomeServidorConectado = "";

  return "Saindo do servidor \'" + nomeServidor + "\'.";
}

string Sistema::list_participants() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "Não há um servidor conectado no momento.";

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
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  vector<string> canaisTexto = findServidor->getCanaisTexto();
  vector<string> canaisVoz = findServidor->getCanaisVoz();

  if (canaisTexto.empty() && canaisVoz.empty()) return "Nenhum canal no servidor foi encontrado.";

  string canais;

  if (!canaisTexto.empty()) {
    canais += "#canais de texto\n";

    for (auto findCanal = canaisTexto.begin(); findCanal != canaisTexto.end(); findCanal++) {
      if (findCanal != canaisTexto.end()) canais += *findCanal + "\n";
    }
  }

  if (!canaisVoz.empty()) {
    canais += "#canais de voz\n";

    for (auto findCanal = canaisVoz.begin(); findCanal != canaisVoz.end(); findCanal++) {
      if (findCanal != canaisVoz.end()) canais += *findCanal + "\n";
    }
  }

  return canais;
}

string Sistema::create_channel(const string nome, const string tipo) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nome.empty()) return "Não é possível criar um canal sem nome.";

  if (tipo != "texto" && tipo != "voz") return "Tipo inválido.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  if (tipo == "texto") {
    vector<string> canaisTexto = findServidor->getCanaisTexto();

    auto findCanal = find_if(canaisTexto.begin(), canaisTexto.end(), [nome](string nomeCanal) {
      return nomeCanal == nome;
    });

    if (findCanal != canaisTexto.end()) return "Canal de texto \'" + nome + "\' já existe.";

    shared_ptr <CanalTexto> newCanal(new CanalTexto(nome, tipo));

    bool canalCriado = findServidor->createCanal(newCanal);

    salvar();

    if (canalCriado) return "Canal de texto \'" + nome + "\' criado.";

    return "Erro ao criar canal de texto.";
  } else {
    vector<string> canaisVoz = findServidor->getCanaisVoz();

    auto findCanal = find_if(canaisVoz.begin(), canaisVoz.end(), [nome](string nomeCanal) {
      return nomeCanal == nome;
    });

    if (findCanal != canaisVoz.end()) return "Canal de voz \'" + nome + "\' já existe.";

    shared_ptr <CanalVoz> newCanal(new CanalVoz(nome, tipo));

    bool canalCriado = findServidor->createCanal(newCanal);

    salvar();

    if (canalCriado) return "Canal de voz \'" + nome + "\' criado.";

    return "Erro ao criar canal de voz.";
  }
}

string Sistema::enter_channel(const string nome, const string tipo) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nome.empty()) return "Não é possível entrar em um canal sem nome.";

  if (tipo != "texto" && tipo != "voz") return "Tipo inválido.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  vector<string> findCanaisTexto = findServidor->getCanaisTexto();
  auto itCanalTexto = find_if(findCanaisTexto.begin(), findCanaisTexto.end(), [nome](std::string nomeCanal) {
    return nomeCanal == nome;
  });

  vector<string> findCanaisVoz = findServidor->getCanaisVoz();
  auto itCanalVoz = find_if(findCanaisVoz.begin(), findCanaisVoz.end(), [nome](std::string nomeCanal) {
    return nomeCanal == nome;
  });

  if (itCanalTexto != findCanaisTexto.end() && itCanalVoz != findCanaisVoz.end()) {
    nomeCanalConectado = nome;

    return "Entrou no canal de " + tipo + " \'" + nome + "\'.";
  } else {
    nomeCanalConectado = nome;

    return "Entrou no canal \'" + nome + "\'.";
  }
}

string Sistema::leave_channel() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nomeCanalConectado.empty()) return "O usuário não está conectado a um canal no momento.";

  string nomeCanal = nomeCanalConectado;

  nomeCanalConectado = "";

  return "Saindo do canal \'" + nomeCanal + "\'.";
}

string Sistema::send_message(const string mensagem) {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nomeCanalConectado.empty()) return "O usuário não está conectado a um canal no momento.";

  if (mensagem.empty()) return "Não é possível enviar uma mensagem vazia.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  char dataHora[100];
  time_t current = time(nullptr);

  strftime(dataHora, 50, "%d/%m/%Y - %R", localtime(&current));

  Mensagem newMensagem(dataHora, mensagem, usuarioLogadoId);

  findServidor->sendMensagem(nomeCanalConectado, newMensagem);

  salvar();

  return "Mensagem enviada.";
}

string Sistema::list_messages() {
  carregar();

  if (!usuarioLogadoId) return "Não há um usuário conectado no momento.";

  if (nomeServidorConectado.empty()) return "O usuário não está conectado a um servidor no momento.";

  if (nomeCanalConectado.empty()) return "O usuário não está conectado a um canal no momento.";

  string nomeServidor = nomeServidorConectado;

  auto findServidor = find_if(servidores.begin(), servidores.end(), [nomeServidor](Servidor servidor) {
    return servidor.getNome() == nomeServidor;
  });

  vector<Mensagem> listaMensagens = findServidor->getMensagens(nomeCanalConectado);

  if (listaMensagens.empty()) return "Não há mensagens no momento.";

  string mensagens;

  for(auto itMensagem = listaMensagens.begin(); itMensagem != listaMensagens.end(); itMensagem++)
    mensagens += usuarios[itMensagem->getEnviadaPor() - 1].getNome() + " <" + itMensagem->getDataHora() + ">: " + itMensagem->getConteudo() + "\n";

  return mensagens;
}

void Sistema::salvarUsuarios() {
  ofstream file("usuarios.txt");

  if (!file) {
    cerr << "Houve um problema ao criar o arquivo." << endl;
    exit(1);
  }

  file << usuarios.size() << endl;

  for (int i = 0; i < usuarios.size(); i++) {
    file << usuarios[i].getId() << endl;
    file << usuarios[i].getNome() << endl;
    file << usuarios[i].getEmail() << endl;
    file << usuarios[i].getSenha() << endl;
  }

  file.close();
}

void Sistema::salvarServidores() {
  ofstream file("servidores.txt");

  if (!file) {
    cerr << "Houve um problema ao criar o arquivo." << endl;
    exit(1);
  }

  file << servidores.size() << endl;

  for (int itServidores = 0; itServidores < servidores.size(); itServidores++) {
    file << servidores[itServidores].getUsuarioDonoId() << endl;
    file << servidores[itServidores].getNome() << endl;
    file << servidores[itServidores].getDescricao() << endl;
    file << servidores[itServidores].getCodigoConvite() << endl;

    file << servidores[itServidores].getParticipantesIds().size() << endl;

    for (int itParticipante = 0; itParticipante < servidores[itServidores].getParticipantesIds().size(); itParticipante++) {
      file << servidores[itServidores].getParticipantesIds()[itParticipante] << endl;
    }

    file << (servidores[itServidores].getCanais().size()) << endl;

    for (int itCanal = 0; itCanal < servidores[itServidores].getCanais().size(); itCanal++) {
      file << servidores[itServidores].getCanais()[itCanal]->getNome() << endl;
      file << servidores[itServidores].getCanais()[itCanal]->getTipo() << endl;
      file << servidores[itServidores].getCanais()[itCanal]->getMensagens().size() << endl;

      for (int itMensagens = 0; itMensagens < servidores[itServidores].getCanais()[itCanal]->getMensagens().size(); itMensagens++) {
        file << servidores[itServidores].getCanais()[itCanal]->getMensagens()[itMensagens].getEnviadaPor() << endl;
        file << servidores[itServidores].getCanais()[itCanal]->getMensagens()[itMensagens].getDataHora() << endl;
        file << servidores[itServidores].getCanais()[itCanal]->getMensagens()[itMensagens].getConteudo() << endl;
      }
    }
  }

  file.close();
}

void Sistema::carregarUsuarios() {
  ifstream file("usuarios.txt");

  if (!file) {
    cout << "Não foi possível abrir o arquivo." << endl;
    exit(1);
  }

  string size, id, nome, email, senha;
  int sizeUsuarios;

  file >> size;
  sizeUsuarios = stoi(size);

  file.ignore();

  for (int itUsuarios = 0; itUsuarios < sizeUsuarios; itUsuarios++) {
    getline(file, id);
    getline(file, nome);
    getline(file, email);
    getline(file, senha);

    int usuarioId = stoi(id);

    auto findUsuario = find_if(usuarios.begin(), usuarios.end(), [usuarioId](Usuario usuario) {
      return usuarioId == usuario.getId();
    });

    if (findUsuario == usuarios.end()) {
      Usuario newUsuario(usuarioId, nome, email, senha);
      usuarios.push_back(newUsuario);
    }
  }

  file.close();
}

void Sistema::carregarServidores() {
  ifstream file("servidores.txt");

  if (!file) {
    cout << "Não foi possível abrir o arquivo." << endl;
    exit(1);
  }

  string size, id, nome, descricao, codigoConvite, nomeCanal, tipoCanal, data, texto;
  int sizeServidores, sizeUsuarios, sizeCanais, sizeMensagens;

  servidores.clear();

  file >> size;
  sizeServidores = stoi(size);

  file.ignore();

  for (int itServidores = 0; itServidores < sizeServidores; itServidores ++) {
    getline(file, id);
    getline(file, nome);
    getline(file, descricao);
    getline(file, codigoConvite);

    int servidorId = stoi(id);

    Servidor newServidor(servidorId, nome);
    newServidor.setDescricao(descricao);
    if (codigoConvite.empty()) newServidor.setCodigoConvite("");
    else newServidor.setCodigoConvite(codigoConvite);

    getline(file, size);
    sizeUsuarios = stoi(size);

    for (int itUsuarios = 0; itUsuarios < sizeUsuarios; itUsuarios++) {
      getline(file, id);
      newServidor.pushParticipante(stoi(id));
    }

    getline(file, size);
    sizeCanais = stoi(size);

    for (int itCanais = 0; itCanais < sizeCanais; itCanais++) {
      getline(file, nomeCanal);
      getline(file, tipoCanal);

      shared_ptr <Canal> newCanal;

      if (tipoCanal == "texto") {
        shared_ptr <CanalTexto> newCanal(new CanalTexto(nomeCanal, tipoCanal));

        getline(file, size);
        sizeMensagens = stoi(size);

        for (int itMensagens = 0; itMensagens < sizeMensagens; itMensagens++) {
          getline(file, id);
          getline(file, data);
          getline(file, texto);

          Mensagem newMensagem(data, texto, stoi(id));
          newCanal->sendMensagem(newMensagem);
        }

        newServidor.createCanal(newCanal);
      } else {
        shared_ptr <CanalVoz> newCanal(new CanalVoz(nomeCanal, tipoCanal));

        getline(file, size);
        sizeMensagens = stoi(size);

        for (int itMensagens = 0; itMensagens < sizeMensagens; itMensagens++) {
          getline(file, id);
          getline(file, data);
          getline(file, texto);

          Mensagem newMensagem(data, texto, stoi(id));
          newCanal->sendMensagem(newMensagem);
        }

        newServidor.createCanal(newCanal);
      }
    }

    servidores.push_back(newServidor);
  }

  file.close();
}

void Sistema::salvar() {
  salvarUsuarios();
  salvarServidores();
}

void Sistema::carregar() {
  carregarUsuarios();
  carregarServidores();
}
