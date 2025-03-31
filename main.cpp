#include "GUI/header/MainWindow.h"
#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include "Logica/header/JSONController.h"
#include "qfiledialog.h"
#include "qhashfunctions.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  Biblioteca biblioteca = Biblioteca();
  AppContext::provide(&biblioteca);
  QApplication app(argc, argv);
  QString path;
  do {
    path = QFileDialog::getOpenFileName(nullptr, "File Json", "", "*.json");
  } while (path.isEmpty());
  AppContext::provide(path);
  JSONController::loadFromFile(biblioteca, path);
  MainWindow mainWindow;
  mainWindow.show();
  app.setStyleSheet("* {background-color: #1e2122;}");
  return app.exec();
}
