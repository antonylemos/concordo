#ifndef CANAL_HPP
#define CANAL_HPP
#include <string>

using namespace std;

class Canal {
  protected:
    string nome;

  public:
    Canal();
    Canal(string const nome);
    ~Canal();

    virtual string getNome() const;
    virtual void setNome(string const nome);
};

#endif
