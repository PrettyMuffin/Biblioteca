#include "../header/Libro.h"
#include "qjsonobject.h"

Libro::Libro(const QString &titolo, const QString &genere,
             const QString &descrizione, const QString &e, const QString &isbn,
             const unsigned short int &usita)
    : ElementoBiblioteca(titolo, genere, descrizione, usita), editore(e),
      ISBN(isbn) {}

QString Libro::JSON_FIELDS::Titolo = ElementoBiblioteca::JSON_FIELDS::Titolo;
QString Libro::JSON_FIELDS::Genere = ElementoBiblioteca::JSON_FIELDS::Genere;
QString Libro::JSON_FIELDS::Descrizione =
    ElementoBiblioteca::JSON_FIELDS::Descrizione;
QString Libro::JSON_FIELDS::Editore = "editore";
QString Libro::JSON_FIELDS::ISBN = "isbn";
QString Libro::JSON_FIELDS::Uscita = ElementoBiblioteca::JSON_FIELDS::Uscita;

QJsonObject Libro::toJson() const {
  QJsonObject libro;
  QJsonObject parent = ElementoBiblioteca::toJson();
  libro[JSON_FIELDS::Titolo] = parent[JSON_FIELDS::Titolo];
  libro[JSON_FIELDS::Genere] = parent[JSON_FIELDS::Genere];
  libro[JSON_FIELDS::Descrizione] = parent[JSON_FIELDS::Descrizione];
  libro[JSON_FIELDS::Uscita] = parent[JSON_FIELDS::Uscita];
  libro[JSON_FIELDS::Editore] = editore;
  libro[JSON_FIELDS::ISBN] = ISBN;
  return libro;
}
