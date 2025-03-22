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
    static QString Valutazione;
    static QString Casa_Cinematografica;
  };
  Film() = default;
  Film(const QString &, const QString &, const QString &, const QString &,
       const std::vector<QString> &, const unsigned short int &,
       const unsigned short int &);
  Film *clone() const override;
  void accept(ElementoBibliotecaVisitor *) override;
  QJsonObject toJson() const override;
  void fromJson(const QJsonObject &) override;
  QString getId() const override;
  QString toString() const override;

  QString getCasaCinematografica() const;
  unsigned short int getValutazione() const;

  Film &operator=(const Film &other);
};

#endif
