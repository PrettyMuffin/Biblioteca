#include "Biblioteca.h"
#include "qcoreapplication.h"
#include <stdexcept>

class AppContext {
public:
  // Metodo per registrare un'istanza di Biblioteca
  static void provide(Biblioteca *);
  static void provide(const QString &);

  // Metodo per ottenere l'istanza di Biblioteca
  static Biblioteca *getBiblioteca();
  static QString *getFilePath();

private:
  static Biblioteca *biblioteca; // Puntatore all'istanza di Biblioteca
  static QString filePath;
};
