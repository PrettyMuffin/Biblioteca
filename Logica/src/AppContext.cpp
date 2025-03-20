#include "../header/AppContext.h"

void AppContext::provide(Biblioteca *nuova_biblioteca)
{
    biblioteca = nuova_biblioteca;
}

Biblioteca *AppContext::getBiblioteca()
{
    if (!biblioteca)
    {
        throw std::runtime_error("Nessuna istanza di Biblioteca registrata!");
    }
    return biblioteca;
}

Biblioteca *AppContext::biblioteca = nullptr;
