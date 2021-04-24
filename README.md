# Concordo - Discord Clone

# 🔖 Sumário

- [Sobre](#%EF%B8%8F-sobre)
- [Tecnologias utilizadas](#-tecnologias-utilizadas)
- [Como baixar e executar?](#-como-baixar-e-executar)
  - [Baixando o projeto](#%EF%B8%8F-baixando-o-projeto)
  - [Executando](#-executando)
- [Comandos do sistema](#-comandos-do-sistema)


## 🏷️ Sobre

O **Concordo** é um projeto desenvolvido na disciplina de Linguagem de Programação I do curso de Tecnologia da Informação da UFRN.

## 🚀 Tecnologias utilizadas

Para o desenvolvimento do **Concordo** foi utilizado apenas **C++**.

## 📦 Como baixar e executar?

**Antes de baixar e executar o projeto**, é necessário ter o [Git](https://git-scm.com/) instalado.

### ⬇️ Baixando o projeto

Abra o terminal do seu sistema operacional e execute os seguintes comandos:

```bash
  # Clonar o repositório
  git clone https://github.com/antonylemos/concordo.git

  # Entrar no diretório
  cd concordo

  # Compilar o programa
  make
```

### 🏃 Executando

Você pode rodar o sistema e em logo depois digitar os comandos seguidos de _ENTER_.
```bash
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```bash
# Primeira parte
./concordo < script_comandos.txt
# Segunda parte
./concordo < script_comandos_final.txt
```

## 📌 Comandos do sistema

Para testar a aplicação, você poderá utilizar os seguintes comandos:

#### `quit`

Fecha a aplicação.
```text
quit
Saindo...
```

#### `create-user`

Cria um usuário utilizando email, senha e nome.
```text
create-user renan@imd.ufrn.br senha Renan
Usuário criado!
```

#### `login`

Faz login do usuário utilizando email (único) e senha.
```text
login renan@imd.ufrn.br senha
Login realizado como renan@imd.ufrn.br!
```

#### `disconnect`

Desconecta usuário logado, caso haja.
```text
disconnect
Desconectando usuário realizado como renan@imd.ufrn.br.
```

#### `create-server`

Cria um servidor utilizando nome (único) caso haja um usuário logado.
```text
create-server servidor-legal
Servidor criado.

create-server servidor-ruim
Servidor criado.

create-server servidor-bacana
Servidor criado.
```

#### `set-server-desc`

Altera a descrição de um servidor caso haja um servidor conectado e um usuário logado, e este seja dono do servidor.
```text
set-server-desc servidor-legal
Descrição do servidor servidor-legal modificada.
```

#### `set-server-invite-code`

Altera o código de convite de um servidor caso haja um servidor conectado e um usuário logado, e este seja dono do servidor.
```text
set-server-invite-code servidor-legal 123
Código de convite do servidor servidor-legal modificado.
```

#### `list-servers`

Lista os servidores cadastrados.
```text
list-servers
servidor-legal
```

#### `remove-server`

Remove um servidor.
```text
remove-server servidor-ruim
Servidor servidor-ruim removido.
```

#### `enter-server`

Entra em um servidor.
```text
enter-server servidor-bacana
Entrou no servidor com sucesso.
```

#### `leave-server`

Sai de um servidor.
```text
leave-server servidor-bacana
Saindo do servidor 'servidor-bacana'.
```

#### `list-participants`

Lista participantes de um determinado servidor.
```text
enter-server servidor-legal
Entrou no servidor com sucesso.

list-participants
Renan
```

#### `create-channel`

Cria um canal em um determinado servidor do tipo 'texto' ou 'voz'.
```text
create-channel canal-legal texto
Canal de texto 'canal-legal' criado.

create-channel canal-ruim texto
Canal de texto 'canal-ruim' criado.
```

#### `list-channels`

Lista canais de um determinado servidor.
```text
list-channels
#canais de texto
canal-legal
canal-ruim
```

#### `enter-channel`

Entra em um canal de um determinado servidor.
```text
enter-channel canal-ruim
Entrou no canal 'canal ruim'.
```

#### `leave-channel`

Entra em um canal de um determinado servidor.
```text
leave-channel
Saindo do canal 'canal ruim'.
```

#### `send-message`

Envia uma mensagem contento um texto para um canal.
```text
send_message As ferias ja chegaram?
```

#### `list-messages`

Lista todas as mensagens de um canal.
```text
list-messages
Renan<08/03/2021 - 12:00>: As ferias ja chegaram?
```

---

Desenvolvido com 💜 por Antony Lemos 🧑🏽‍🚀
