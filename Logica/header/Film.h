#ifndef FILM_H
#define FILM_H

#include "ElementoBiblioteca.h"
#include "Persona.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include <vector>

class Film : public ElementoBiblioteca {
private:
  std::vector<Persona> cast;
  unsigned short int valutazione;
  QString casa_cinematografica;

public:
  QJsonObject toJson() const override;
};

#endif
