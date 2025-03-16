#include "GUI/header/MainWindow.h"
#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  Biblioteca biblioteca = Biblioteca();
  AppContext::provide(&biblioteca);

  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
