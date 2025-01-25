#ifndef BRANO_H
#define BRANO_H

#include "Biblioteca.h"
#include "ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"

class Brano : public ElementoBiblioteca {
private:
  QString album;
  unsigned int durata; // secondi
public:
  QJsonObject toJson() const override;
};

#endif
