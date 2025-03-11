#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include "qapplication.h"
#include "qlabel.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
  Biblioteca biblioteca = Biblioteca();
  AppContext::provide(&biblioteca);

  QApplication app(argc, argv);
  QLabel hello("Hello world!");
  hello.show();
  return app.exec();
}
