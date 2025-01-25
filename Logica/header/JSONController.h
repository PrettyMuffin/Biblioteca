#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include "Biblioteca.h"

class JSONController {
public:
  void loadFromFile(Biblioteca &, const QString &);
  void saveOnFile(Biblioteca &, const QString &);
};

#endif
