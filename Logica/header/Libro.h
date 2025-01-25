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
  QJsonObject toJson() const override;
};

#endif
