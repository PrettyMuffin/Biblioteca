#ifndef JSON_ERROR_H
#define JSON_ERROR_H

#include "qcoreapplication.h"
class JSONError {
private:
  QString message;

public:
  JSONError(const QString &);
  QString getMessage() const;
};

#endif
