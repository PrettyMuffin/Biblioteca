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
  QString casa_cinematografica;
  unsigned short int valutazione;

public:
  struct JSON_FIELDS {
    static QString Valutazione;
    static QString Casa_Cinematografica;
  };
  Film() = default;
  Film(const Film &);
  Film(const QString &, const QString &, const QString &, const QString &,
       const QVector<QString> &, const unsigned short int &,
       const unsigned short int &, const QString &);
  Film *clone() const override;
  void accept(ElementoBibliotecaVisitor *) override;
  QJsonObject toJson() const override;
  void fromJson(const QJsonObject &) override;
  QString getId() const override;
  QString toString() const override;

  QString getCasaCinematografica() const;
  unsigned short int getValutazione() const;

  Film &operator=(const Film &other);
  Film &operator=(const ElementoBiblioteca &other) override;
};

#endif
