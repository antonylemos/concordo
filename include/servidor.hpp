#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP
#include <string>
#include <vector>
#include <memory>

#include "canal.hpp"
#include "canal_texto.hpp"
#include "canal_voz.hpp"

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
    Servidor();
    Servidor(int usuarioDonoId, string nome);
    ~Servidor();

    int getUsuarioDonoId() const;
    void setUsuarioDonoId(int const usuarioDonoId);

    string getNome() const;
    void setNome(string const nome);

    string getDescricao() const;
    void setDescricao(string const descricao);

    string getCodigoConvite() const;
    void setCodigoConvite(string const codigoConvite);

    vector<int> getParticipantesIds();

    vector<string> getCanaisTexto() const;
    vector<string> getCanaisVoz() const;

    bool createCanal(shared_ptr <Canal> canal);

    bool pushParticipante(int const participanteId);
};

#endif
