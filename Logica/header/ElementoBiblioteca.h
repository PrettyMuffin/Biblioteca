#ifndef ELEMENTOBIBIBLIOTECA_H
#define ELEMENTOBIBIBLIOTECA_H

#include "ElementoBibliotecaObserver.h"
#include "ElementoBibliotecaVisitor.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include <vector>

class ElementoBiblioteca {
private:
  QString id; // titolo(to lower) + autore(to lower)
  QString titolo;
  QString genere;
  QString descrizione;
  unsigned short int uscita; // anno pubblicazione
  std::vector<ElementoBibliotecaObserver *> observers;

public:
  virtual QJsonObject toJson() const = 0;
  virtual void accept(ElementoBiblotecaVisitor) const = 0;
  void registerObserver(ElementoBibliotecaObserver);
};

#endif
