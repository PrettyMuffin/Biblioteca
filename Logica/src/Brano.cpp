#include "../header/Brano.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"

Brano::Brano(const QString &titolo, const QString &genere,
             const QString &descrizione, const QString &a,
             const unsigned int &d, const QVector<QString> &autori,
             const unsigned short int &uscita, const QString &immagine)
    : ElementoBiblioteca(titolo, genere, descrizione, autori, uscita, immagine),
      album(a), durata(d) {
  id += "brano";
}

Brano::Brano(const Brano &other)
    : ElementoBiblioteca(other), album(other.album), durata(other.durata) {
  id += "brano";
}

QString Brano::JSON_FIELDS::Album = "album";
QString Brano::JSON_FIELDS::Durata = "durata";

QJsonObject Brano::toJson() const {
  QJsonObject brano = ElementoBiblioteca::toJson();
  brano[JSON_FIELDS::Album] = album;
  brano[JSON_FIELDS::Durata] = static_cast<qint64>(durata);
  brano[ElementoBiblioteca::JSON_FIELDS::Tipo] = "brano";
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
  res += QString("album:") + album + ESCAPE_CHAR;
  res += QString("tipo:") + "brano";
  return res.toLower();
}

QString Brano::getAlbum() const { return album; }

unsigned int Brano::getDurata() const { return durata; }

Brano &Brano::operator=(const Brano &other) {
  ElementoBiblioteca::operator=(other);
  album = other.album;
  durata = other.durata;
  return *this;
}
