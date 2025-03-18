#include "GUI/header/MainWindow.h"
#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include "Logica/header/ElementoBibliotecaVisitor.h"
#include "Logica/header/Libro.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  Biblioteca biblioteca = Biblioteca();
  vector<QString> autori = {"autor1", "autor2"};
  biblioteca.add(new Libro("El Principito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("l Principito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("El Principito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro(" Principito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("rincipito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("incipito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("ncipito", "bello", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("ito", "bello", "un libro molto bello", "editore",
                           "33838", autori, 1900));
  biblioteca.add(new Libro("cipito", "bello", "un libro molto bello", "editore",
                           "33838", autori, 1900));

  AppContext::provide(&biblioteca);
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
