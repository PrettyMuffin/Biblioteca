#ifndef PERSONA_H
#define PERSONA_H

#include "qcoreapplication.h"
#include "qdeadlinetimer.h"

class Persona {
private:
  QString nome;
  QString cognome;
  QString nome_arte;
  unsigned short int eta;
  QString bio;

public:
  Persona() = default;
  Persona(const QString &, const QString &, const QString &,
          const unsigned short int &, const QString &);
  QJsonObject toJson() const;
};

#endif
