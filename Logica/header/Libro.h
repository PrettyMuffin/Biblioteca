#ifndef LIBRO_H
#define LIBRO_H

#include "ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"

class Libro : public ElementoBiblioteca {
private:
  QString editore;
  QString ISBN;

public:
  class JSON_FIELDS {
  public:
    static QString Titolo;
    static QString Genere;
    static QString Descrizione;
    static QString Uscita;
    static QString Editore;
    static QString ISBN;
  };
  Libro() = default;
  Libro(const QString &, const QString &, const QString &, const QString &,
        const QString &, const unsigned short int &);
  QJsonObject toJson() const override;
};

#endif
