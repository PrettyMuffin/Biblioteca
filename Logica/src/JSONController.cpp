#include "../header/JSONController.h"
#include "../header/JSONError.h"
#include "qcoreapplication.h"
#include "qjsondocument.h"
#include "qjsonvalue.h"
#include "qobject.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

void JSONController::loadFromFile(Biblioteca &biblioteca,
                                  const QString &filePath) {
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Error opening file: " << filePath;
    return;
  }
  QJsonParseError error;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &error);
  if (error.error != QJsonParseError::NoError) {
    throw JSONError(error.errorString());
  }
  if (!jsonDoc.isArray()) {
    throw JSONError("Invalid JSON format");
  }
  QJsonArray elementiBiblioteca = jsonDoc.array();
  for (auto elemento : elementiBiblioteca) {
  }
}
