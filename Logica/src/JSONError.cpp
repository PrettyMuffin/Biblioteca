#include "../header/JSONError.h"

JSONError::JSONError(const QString &msg) : message(msg) {}
QString JSONError::getMessage() const { return message; }
