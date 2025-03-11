#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include "Biblioteca.h"

class JSONController {
public:
  static void loadFromFile(Biblioteca &, const QString &);
  static void saveOnFile(const Biblioteca &, const QString &);
};

#endif
