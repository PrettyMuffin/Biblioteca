/*
Design pattern Service Locator
Vantaggi del Service Locator
1. Accesso centralizzato: Puoi accedere alla Biblioteca da qualsiasi parte del
programma senza dover passare l'istanza come parametro.

2. Flessibilità: Puoi cambiare l'implementazione della Biblioteca (ad esempio,
usando un mock per i test) senza modificare il codice che la utilizza.

2. Chiarezza: Il codice che utilizza la Biblioteca non deve sapere come essa
viene creata o gestita.

*/

#include "Biblioteca.h"
#include <stdexcept>

class AppContext {
public:
  // Metodo per registrare un'istanza di Biblioteca
  static void provide(Biblioteca *);

  // Metodo per ottenere l'istanza di Biblioteca
  static Biblioteca *getBiblioteca();

private:
  static Biblioteca *biblioteca; // Puntatore all'istanza di Biblioteca
};
