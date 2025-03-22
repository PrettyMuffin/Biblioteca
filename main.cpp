#include "GUI/header/MainWindow.h"
#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include "Logica/header/JSONController.h"
#include "qfiledialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  Biblioteca biblioteca = Biblioteca();
  AppContext::provide(&biblioteca);
  QApplication app(argc, argv);
  JSONController::loadFromFile(
      biblioteca,
      QFileDialog::getOpenFileName(nullptr, "File Json", "", "*.json"));
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
