#include "../../header/Body/ContentView.h"
#include "../../../Logica/header/AppContext.h"
#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"
#include "../../header/Body/FilterView.h"

#include "qcontainerfwd.h"
#include "qcoreapplication.h"

#include <QRegularExpression>

ContentView::ContentView(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  filtri = new FilterView(this);

  prodotti = new ProductsView(AppContext::getBiblioteca()->getElements(), this);

  layout->addWidget(filtri);
  layout->addWidget(prodotti);

  setLayout(layout);

  connect(filtri, &FilterView::filterChanged, this,
          &ContentView::updateProducts);

  connect(this, &ContentView::onDeleteProduct, prodotti,
          &ProductsView::deleteProduct);
}

ContentView::~ContentView() {
  delete filtri;
  delete prodotti;
}

void ContentView::updateProducts(FilterType tipo, QString query_ricerca) {
  if (tipo == FilterType::LIBRI) {
    prodotti->setProducts(libri());
  } else if (tipo == FilterType::BRANI) {
    prodotti->setProducts(brani());
  } else if (tipo == FilterType::FILM) {
    prodotti->setProducts(film());
  } else if (tipo == FilterType::QUERY) {
    prodotti->setProducts(query(query_ricerca));
  }
}

// ho voluto fare questi metodi e non delegare alla regex la ricerca
// perché non sapevo se effettivamente era consentito, dunque ho usato il
// dynamic cast
QVector<ElementoBiblioteca *> ContentView::libri() {
  QVector<ElementoBiblioteca *> libri;
  QVector<ElementoBiblioteca *> tutti_el =
      AppContext::getBiblioteca()->getElements();
  for (auto el : tutti_el) {
    Libro *libro = dynamic_cast<Libro *>(el);
    if (libro != nullptr) {
      libri.push_back(libro);
    }
  }
  return libri;
}

QVector<ElementoBiblioteca *> ContentView::brani() {
  QVector<ElementoBiblioteca *> brani;
  QVector<ElementoBiblioteca *> tutti_el =
      AppContext::getBiblioteca()->getElements();
  for (auto el : tutti_el) {
    Brano *brano = dynamic_cast<Brano *>(el);
    if (brano != nullptr) {
      brani.push_back(brano);
    }
  }
  return brani;
}

QVector<ElementoBiblioteca *> ContentView::film() {
  QVector<ElementoBiblioteca *> filmi;
  QVector<ElementoBiblioteca *> tutti_el =
      AppContext::getBiblioteca()->getElements();
  for (auto el : tutti_el) {
    Film *film = dynamic_cast<Film *>(el);
    if (film != nullptr) {
      filmi.push_back(film);
    }
  }
  return filmi;
}

QVector<ElementoBiblioteca *> ContentView::query(QString query) {
  return AppContext::getBiblioteca()->search(
      query.removeIf([](QChar c) { return c.isSpace(); }));
}
