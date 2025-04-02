#include "../header/Libro.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"

Libro::Libro(const QString &titolo, const QString &genere,
             const QString &descrizione, const QString &e, const QString &isbn,
             const QVector<QString> &autori, const unsigned short int &usita,
             const QString &immagine)
    : ElementoBiblioteca(titolo, genere, descrizione, autori, usita, immagine),
      editore(e), ISBN(isbn) {
  id += "libro";
}

QString Libro::JSON_FIELDS::Editore = "editore";
QString Libro::JSON_FIELDS::ISBN = "isbn";

QJsonObject Libro::toJson() const {
  QJsonObject libro = ElementoBiblioteca::toJson();
  libro[JSON_FIELDS::Editore] = editore;
  libro[JSON_FIELDS::ISBN] = ISBN;
  libro[ElementoBiblioteca::JSON_FIELDS::Tipo] = "libro";
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
  res += "editore:" + QString(editore).removeIf([](QChar c) {
    return c.isSpace();
  }) + ESCAPE_CHAR;
  res += "isbn:" + QString(ISBN).removeIf([](QChar c) { return c.isSpace(); }) +
         ESCAPE_CHAR;
  res += QString("tipo:") + "libro";
  return res.toLower();
}

QString Libro::getEditore() const { return editore; }

QString Libro::getISBN() const { return ISBN; }

Libro &Libro::operator=(const Libro &other) {
  ElementoBiblioteca::operator=(other);
  editore = other.editore;
  ISBN = other.ISBN;
  return *this;
}
