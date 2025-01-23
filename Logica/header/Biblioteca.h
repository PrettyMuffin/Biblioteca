#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "ElementoBiblioteca.h"
#include "qcoreapplication.h"

#include <map>
using std::map;

class Biblioteca {
private:
  map<QString, ElementoBiblioteca *> tutti_elementi;

public:
  Biblioteca() = default;
  Biblioteca(const map<QString, ElementoBiblioteca> &);
  bool add(ElementoBiblioteca *);
  bool remove(unsigned int);
  bool remove(ElementoBiblioteca *);
  bool update(unsigned int, ElementoBiblioteca *);
  bool update(ElementoBiblioteca *, ElementoBiblioteca *);
  const map<QString, ElementoBiblioteca *> &
  getElements() const; // passo per riferimento così da non dover fare la copia,
                       // tanto lo ritorno costante dunque non vengono fatte
                       // modifiche al di fuori di Biblioteca
};

#endif
