#include "../header/JSONController.h"
#include "../header/JSONError.h"
#include "qcoreapplication.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
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
    throw JSONError("Formato JSON non valido");
  }
  QJsonArray elementiBiblioteca = jsonDoc.array();
  for (auto elemento : elementiBiblioteca) {
    ElementoBiblioteca *nu_e;
    nu_e->fromJson(elemento.toObject());
    ElementoBiblioteca *nuovoElemento = nu_e->clone();
    biblioteca.add(nuovoElemento);
  }
}

void JSONController::saveOnFile(const Biblioteca &biblioteca,
                                const QString &filePath) {
  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly)) {
    throw JSONError("Errore nell'apertura del file di salvataggio");
  }
  QJsonDocument jsonDoc(biblioteca.toJson());
  file.write(jsonDoc.toJson());
}
