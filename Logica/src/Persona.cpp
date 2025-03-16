#include "../header/Persona.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include <QJsonObject>

Persona::Persona(const QString &n, const QString &cogn, const QString &n_arte,
                 const unsigned short int &e, const QString &b)
    : nome(n), cognome(cogn), nome_arte(n_arte), eta(e), bio(b) {}

QJsonObject Persona::toJson() const {
  QJsonObject person;
  person[JSON_FIELDS::Nome] = nome;
  person[JSON_FIELDS::Cognome] = cognome;
  person[JSON_FIELDS::Nome_Arte] = nome_arte;
  person[JSON_FIELDS::Eta] = eta;
  person[JSON_FIELDS::Bio] = bio;
  return person;
}

QString Persona::JSON_FIELDS::Nome = "Nome";
QString Persona::JSON_FIELDS::Cognome = "Nome";
QString Persona::JSON_FIELDS::Nome_Arte = "Nome";
QString Persona::JSON_FIELDS::Eta = "Eta";
QString Persona::JSON_FIELDS::Bio = "Nome";
