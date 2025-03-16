#include "../header/Brano.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"

Brano::Brano(const QString &titolo, const QString &genere,
             const QString &descrizione, const QString &a,
             const unsigned int &d, const std::vector<QString> &autori,
             const unsigned short int &uscita)
    : ElementoBiblioteca(titolo, genere, descrizione, autori, uscita), album(a),
      durata(d) {
  id += "brano";
}

QString Brano::JSON_FIELDS::Titolo = ElementoBiblioteca::JSON_FIELDS::Titolo;
QString Brano::JSON_FIELDS::Genere = ElementoBiblioteca::JSON_FIELDS::Genere;
QString Brano::JSON_FIELDS::Descrizione =
    ElementoBiblioteca::JSON_FIELDS::Descrizione;
QString Brano::JSON_FIELDS::Album = "album";
QString Brano::JSON_FIELDS::Durata = "durata";
QString Brano::JSON_FIELDS::Uscita = ElementoBiblioteca::JSON_FIELDS::Uscita;
QString Brano::JSON_FIELDS::Autori = ElementoBiblioteca::JSON_FIELDS::Autori;
QString Brano::JSON_FIELDS::Tipo = "tipo";

QJsonObject Brano::toJson() const {
  QJsonObject brano;
  QJsonObject parent = ElementoBiblioteca::toJson();

  brano[JSON_FIELDS::Titolo] = parent[JSON_FIELDS::Titolo];
  brano[JSON_FIELDS::Genere] = parent[JSON_FIELDS::Genere];
  brano[JSON_FIELDS::Descrizione] = parent[JSON_FIELDS::Descrizione];
  brano[JSON_FIELDS::Uscita] = parent[JSON_FIELDS::Uscita];
  brano[JSON_FIELDS::Autori] = parent[JSON_FIELDS::Autori];
  brano[JSON_FIELDS::Album] = album;
  brano[JSON_FIELDS::Durata] = static_cast<qint64>(durata);
  brano[JSON_FIELDS::Tipo] = "brano";
  return brano;
}

Brano *Brano::clone() const { return new Brano(*this); }

QString Brano::getId() const { return id; }

void Brano::accept(ElementoBibliotecaVisitor *visitor) { visitor->visit(this); }

void Brano::fromJson(const QJsonObject &json) {
  ElementoBiblioteca::fromJson(json);
  album = json[JSON_FIELDS::Album].toString();
  durata = json[JSON_FIELDS::Durata].toInt();
  id += "brano";
}

QString Brano::toString() const {
  QString res = ElementoBiblioteca::toString();
  res += album + ESCAPE_CHAR;
  res += QString::number(durata) + ESCAPE_CHAR;
  res += "brano";
  return res;
}

QString Brano::getAlbum() const { return album; }

unsigned int Brano::getDurata() const { return durata; }

Brano &Brano::operator=(const Brano &other) {
  ElementoBiblioteca::operator=(other);
  album = other.album;
  durata = other.durata;
  return *this;
}
