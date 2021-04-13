#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP
#include <string>
#include <vector>
#include <memory>

#include "canal.hpp"
#include "canalTexto.hpp"
#include "canalVoz.hpp"

using namespace std;

class Servidor {
  // Atributos da classe
  private:
    int usuarioDonoId;
    string nome;
    string descricao;
    string codigoConvite;
    vector <int> participantesIds;
    vector <shared_ptr <Canal>> canais;

  // Métodos da classe
  public:
    // Construtor
    Servidor();
    // Construtor sobrecarregado
    Servidor(int usuarioDonoId, string nome);
    // Destrutor
    ~Servidor();

    // Retorna o ID do dono do servidor
    int getUsuarioDonoId() const;
    // Altera o ID do dono do servidor
    void setUsuarioDonoId(int const usuarioDonoId);

    // Retorna o nome do servidor
    string getNome() const;
    // Altera o nome do servidor
    void setNome(string const nome);

    // Retorna a descrição do servidor
    string getDescricao() const;
    // Altera a descrição do servidor
    void setDescricao(string const descricao);

    // Retorna o código de convite do servidor
    string getCodigoConvite() const;
    // Altera o código de convite do servidor
    void setCodigoConvite(string const codigoConvite);

    // Retorna um vetor com os ID's dos participantes do servidor
    vector<int> getParticipantesIds();

    // Retorna os canais de texto do servidor
    vector<string> getCanaisTexto() const;
    // Retorna os canais de voz do servidor
    vector<string> getCanaisVoz() const;

    // Cria um canal no servidor
    bool createCanal(shared_ptr <Canal> canal);

    // Adiciona um participante no servidor
    bool pushParticipante(int const participanteId);

    // Retorna um vetor com as mensagens de um canal no servidor
    vector<Mensagem> getMensagens(const string nomeCanal);
    // Envia uma mensagem em um canal no servidor
    void sendMensagem(const string nomeCanal, const Mensagem mensagem);
};

#endif
