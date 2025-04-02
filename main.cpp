#include "GUI/header/MainWindow.h"
#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include "Logica/header/JSONController.h"
#include "Logica/header/JSONError.h"
#include "qfiledialog.h"
#include "qhashfunctions.h"
#include "qmessagebox.h"
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
  try {
    JSONController::loadFromFile(biblioteca, path);
  } catch (JSONError &e) {
    QMessageBox::critical(nullptr, "Error", e.getMessage());
    return 1;
  }
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
