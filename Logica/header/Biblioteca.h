#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "ElementoBiblioteca.h"
#include "qcontainerfwd.h"
#include "qcoreapplication.h"
#include "qglobal.h"
#include "qobject.h"

#include <vector>
using std::vector;

class Biblioteca {
private:
  QVector<ElementoBiblioteca *> tutti_elementi;
  bool Contains(ElementoBiblioteca *) const;

public:
  Biblioteca() = default;
  Biblioteca(const vector<ElementoBiblioteca *> &);
  bool add(ElementoBiblioteca *);
  bool remove(unsigned int);
  bool remove(ElementoBiblioteca *);
  bool update(unsigned int, ElementoBiblioteca *);
  bool update(ElementoBiblioteca *, ElementoBiblioteca *);
  QVector<ElementoBiblioteca *> search(const QString &) const;
  const QVector<ElementoBiblioteca *> getElements() const;
  QJsonArray toJson() const;
};

#endif
