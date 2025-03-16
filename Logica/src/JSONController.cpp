#include "../header/JSONController.h"
#include "../header/Brano.h"
#include "../header/Film.h"
#include "../header/JSONError.h"
#include "../header/Libro.h"
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
    QString tipo =
        elemento.toObject()[ElementoBiblioteca::JSON_FIELDS::Tipo].toString();
    if (tipo == "libro") {
      nu_e = new Libro();
      nu_e->fromJson(elemento.toObject());
    } else if (tipo == "film") {
      nu_e = new Film();
      nu_e->fromJson(elemento.toObject());
    } else if (tipo == "brano") {
      nu_e = new Brano();
      nu_e->fromJson(elemento.toObject());
    } else {
      throw JSONError("Tipo di elemento non valido");
    }
    biblioteca.add(nu_e);
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
