#include "../header/Brano.h"
#include "qjsonobject.h"

Brano::Brano(const QString &titolo, const QString &genere,
             const QString &descrizione, const QString &a,
             const unsigned int &d, const unsigned short int &uscita)
    : ElementoBiblioteca(titolo, genere, descrizione, uscita), album(a),
      durata(d) {}

QString Brano::JSON_FIELDS::Titolo = ElementoBiblioteca::JSON_FIELDS::Titolo;
QString Brano::JSON_FIELDS::Genere = ElementoBiblioteca::JSON_FIELDS::Genere;
QString Brano::JSON_FIELDS::Descrizione =
    ElementoBiblioteca::JSON_FIELDS::Descrizione;
QString Brano::JSON_FIELDS::Album = "album";
QString Brano::JSON_FIELDS::Durata = "durata";
QString Brano::JSON_FIELDS::Uscita = ElementoBiblioteca::JSON_FIELDS::Uscita;

QJsonObject Brano::toJson() const {
  QJsonObject brano;
  QJsonObject parent = ElementoBiblioteca::toJson();

  brano[JSON_FIELDS::Titolo] = parent[JSON_FIELDS::Titolo];
  brano[JSON_FIELDS::Genere] = parent[JSON_FIELDS::Genere];
  brano[JSON_FIELDS::Descrizione] = parent[JSON_FIELDS::Descrizione];
  brano[JSON_FIELDS::Uscita] = parent[JSON_FIELDS::Uscita];
  brano[JSON_FIELDS::Album] = album;
  brano[JSON_FIELDS::Durata] = static_cast<qint64>(durata);
  return brano;
}
