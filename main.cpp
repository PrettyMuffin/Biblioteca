#include "GUI/header/MainWindow.h"
#include "Logica/header/AppContext.h"
#include "Logica/header/Biblioteca.h"
#include "Logica/header/ElementoBibliotecaVisitor.h"
#include "Logica/header/Libro.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  Biblioteca biblioteca = Biblioteca();
  vector<QString> autori = {"autor1", "autor2"};
  biblioteca.add(new Libro("Biografia2", "Biografia", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("l Principito", "e", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("El Principito", "arg", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("autor3", "f", "un libro molto bello", "editore",
                           "33838", autori, 1900));
  biblioteca.add(new Libro("rincipito", "faslkj", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("incipito", "fasflaskfaslfj", "un libro molto bello",
                           "editore", "33838", autori, 1900));
  biblioteca.add(new Libro("ncipito", "flaksfjl", "un libro molto bello",
                           "editore", "33838", {"agassi"}, 1900));
  biblioteca.add(new Libro("ito", "faslfjsa", "un libro molto bello", "editore",
                           "33838", {"autor3, autor4"}, 1900));
  biblioteca.add(new Libro("Biografia Agassi", "becwllo",
                           "un libro molto bello", "editore", "33838",
                           {"autor2", "autor3"}, 1900));

  AppContext::provide(&biblioteca);
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
