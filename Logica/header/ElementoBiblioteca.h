#ifndef ELEMENTOBIBIBLIOTECA_H
#define ELEMENTOBIBIBLIOTECA_H

#include "ElementoBibliotecaObserver.h"
#include "ElementoBibliotecaVisitor.h"
#include "Persona.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include "qset.h"
#include <vector>

class ElementoBiblioteca {
private:
  QString id; // titolo(to lower) + autore(to lower)
  QString titolo;
  QString genere;
  QString descrizione;
  const std::vector<QString> autori;
  unsigned short int uscita; // anno pubblicazione
  std::vector<ElementoBibliotecaObserver *> observers;

public:
  class JSON_FIELDS {
  public:
    static QString Titolo;
    static QString Genere;
    static QString Descrizione;
    static QString Autori;
    static QString Uscita;
  };
  ElementoBiblioteca() = default;
  ElementoBiblioteca(const QString &, const QString &, const QString &,
                     const std::vector<QString> &, const unsigned short int &);
  virtual QJsonObject toJson() const = 0;
  virtual void accept(ElementoBiblotecaVisitor) const = 0;
  void registerObserver(ElementoBibliotecaObserver);
  virtual ~ElementoBiblioteca() = default;
};

#endif
