#include "../header/Libro.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"

Libro::Libro(const QString &titolo, const QString &genere,
             const QString &descrizione, const QString &e, const QString &isbn,
             const std::vector<QString> &autori,
             const unsigned short int &usita)
    : ElementoBiblioteca(titolo, genere, descrizione, autori, usita),
      editore(e), ISBN(isbn) {
  id += "libro";
}

QString Libro::JSON_FIELDS::Titolo = ElementoBiblioteca::JSON_FIELDS::Titolo;
QString Libro::JSON_FIELDS::Genere = ElementoBiblioteca::JSON_FIELDS::Genere;
QString Libro::JSON_FIELDS::Descrizione =
    ElementoBiblioteca::JSON_FIELDS::Descrizione;
QString Libro::JSON_FIELDS::Editore = "editore";
QString Libro::JSON_FIELDS::ISBN = "isbn";
QString Libro::JSON_FIELDS::Uscita = ElementoBiblioteca::JSON_FIELDS::Uscita;
QString Libro::JSON_FIELDS::Autori = ElementoBiblioteca::JSON_FIELDS::Autori;
QString Libro::JSON_FIELDS::Tipo = "tipo";

QJsonObject Libro::toJson() const {
  QJsonObject libro;
  QJsonObject parent = ElementoBiblioteca::toJson();

  libro[JSON_FIELDS::Titolo] = parent[JSON_FIELDS::Titolo];
  libro[JSON_FIELDS::Genere] = parent[JSON_FIELDS::Genere];
  libro[JSON_FIELDS::Descrizione] = parent[JSON_FIELDS::Descrizione];
  libro[JSON_FIELDS::Uscita] = parent[JSON_FIELDS::Uscita];
  libro[JSON_FIELDS::Autori] = parent[JSON_FIELDS::Autori];
  libro[JSON_FIELDS::Editore] = editore;
  libro[JSON_FIELDS::ISBN] = ISBN;
  libro[JSON_FIELDS::Tipo] = "libro";
  return libro;
}

QString Libro::getId() const { return id; }

Libro *Libro::clone() const { return new Libro(*this); }

void Libro::accept(ElementoBibliotecaVisitor *vi) { vi->visit(this); }

void Libro::fromJson(const QJsonObject &json) {
  ElementoBiblioteca::fromJson(json);
  editore = json[JSON_FIELDS::Editore].toString();
  ISBN = json[JSON_FIELDS::ISBN].toString();
  id += "libro";
}

QString Libro::toString() const {
  QString res = ElementoBiblioteca::toString();
  res += editore + ESCAPE_CHAR;
  res += ISBN + ESCAPE_CHAR;
  res += "libro";
  return res;
}

QString Libro::getEditore() const { return editore; }

QString Libro::getISBN() const { return ISBN; }

Libro &Libro::operator=(const Libro &other) {
  ElementoBiblioteca::operator=(other);
  editore = other.editore;
  ISBN = other.ISBN;
  return *this;
}
