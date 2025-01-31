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
  class JSON_FIELDS {
  public:
    static QString Nome;
    static QString Cognome;
    static QString Nome_Arte;
    static QString Eta;
    static QString Bio;
  };
  Persona() = default;
  Persona(const QString &, const QString &, const QString &,
          const unsigned short int &, const QString &);
  QJsonObject toJson() const;
};

#endif
