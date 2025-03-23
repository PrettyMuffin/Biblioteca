#include "../header/Film.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"

Film::Film(const QString &titolo, const QString &genere,
           const QString &descrizione, const QString &ca_cin,
           const QVector<QString> &autori, const unsigned short int &uscita,
           const unsigned short int &valutazione)
    : ElementoBiblioteca(titolo, genere, descrizione, autori, uscita),
      casa_cinematografica(ca_cin), valutazione(valutazione) {
  id += "film";
}

QString Film::JSON_FIELDS::Valutazione = "valutazione";
QString Film::JSON_FIELDS::Casa_Cinematografica = "casa";

QJsonObject Film::toJson() const {
  QJsonObject film = ElementoBiblioteca::toJson();
  film[JSON_FIELDS::Valutazione] = valutazione;
  film[JSON_FIELDS::Casa_Cinematografica] = casa_cinematografica;
  film[ElementoBiblioteca::JSON_FIELDS::Tipo] = "film";
  return film;
}
Film *Film::clone() const { return new Film(*this); }

void Film::accept(ElementoBibliotecaVisitor *visitor) { visitor->visit(this); }

QString Film::getId() const { return id; }

void Film::fromJson(const QJsonObject &json) {
  ElementoBiblioteca::fromJson(json);
  casa_cinematografica = json[JSON_FIELDS::Casa_Cinematografica].toString();
  valutazione = json[JSON_FIELDS::Valutazione].toInt();
  id += "film";
}

QString Film::toString() const {
  QString res = ElementoBiblioteca::toString();
  res += "casacinematografica:" +
         QString(casa_cinematografica).removeIf([](QChar c) {
           return c.isSpace();
         }) +
         ESCAPE_CHAR;
  res += "valutazione:" +
         QString(QString::number(valutazione))
             .removeIf([](QChar c) { return c.isSpace(); })
             .toLower() +
         ESCAPE_CHAR;
  res += QString("tipo:") + "film";
  return res.toLower();
}

QString Film::getCasaCinematografica() const { return casa_cinematografica; }

unsigned short int Film::getValutazione() const { return valutazione; }

Film &Film::operator=(const Film &other) {
  ElementoBiblioteca::operator=(other);
  casa_cinematografica = other.casa_cinematografica;
  valutazione = other.valutazione;
  return *this;
}
