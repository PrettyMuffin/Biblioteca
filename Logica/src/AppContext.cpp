#include "../header/AppContext.h"
#include "qcoreapplication.h"

void AppContext::provide(Biblioteca *nuova_biblioteca) {
  biblioteca = nuova_biblioteca;
}

void AppContext::provide(const QString &path) { filePath = path; }

Biblioteca *AppContext::getBiblioteca() {
  if (!biblioteca) {
    throw std::runtime_error("Nessuna istanza di Biblioteca registrata!");
  }
  return biblioteca;
}

QString *AppContext::getFilePath() { return &filePath; }

Biblioteca *AppContext::biblioteca = nullptr;

QString AppContext::filePath = "";
