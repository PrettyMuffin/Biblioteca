#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include "Biblioteca.h"

class JSONController {
public:
  void loadFromFile(Biblioteca &, const QString &);
  void saveOnFile(const Biblioteca &, const QString &);
};

#endif
