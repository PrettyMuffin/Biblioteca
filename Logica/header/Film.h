#ifndef FILM_H
#define FILM_H

#include "ElementoBiblioteca.h"
#include "ElementoBibliotecaVisitor.h"
#include "Persona.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include <vector>

class Film : public ElementoBiblioteca {
private:
  unsigned short int valutazione;
  QString casa_cinematografica;

public:
  class JSON_FIELDS {
  public:
    static QString Titolo;
    static QString Genere;
    static QString Descrizione;
    static QString Autori;
    static QString Uscita;
    static QString Valutazione;
    static QString Casa_Cinematografica;
  };
  Film() = default;
  Film(const QString &, const QString &, const QString &, const QString &,
       const std::vector<QString> &, const unsigned short int &,
       const unsigned short int &);
  void accept(ElementoBiblotecaVisitor *) override;
  QJsonObject toJson() const override;
};

#endif
