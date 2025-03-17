#include "../../header/Body/ProductsView.h"
#include "../../../Logica/header/AppContext.h"
#include "qcoreapplication.h"
#include "qlabel.h"
#include "qpixmap.h"
#include "qscrollarea.h"
#include "qwidget.h"
#include <cstdlib>

ProductsView::ProductsView(QWidget *parent) : QWidget(parent) {
  scrollArea = new QScrollArea(this);
  QWidget *scrollContent = new QWidget(scrollArea);

  layout = new QGridLayout(scrollContent);
  Biblioteca *biblioteca = AppContext::getBiblioteca();
  for (auto elemento : biblioteca->getElements()) {
    ProductCard *card = new ProductCard(elemento, this);
    layout->addWidget(card);
  }
  scrollContent->setLayout(layout);
  scrollArea->setWidget(scrollContent);
  scrollArea->setWidgetResizable(true);
}

ProductsView::~ProductsView() { delete layout; }

ProductCard::ProductCard(ElementoBiblioteca *elemento, QWidget *parent)
    : QWidget(parent) {
  layout = new QVBoxLayout(this);
  copertina = new QLabel("", this);
  titolo = new QLabel(elemento->getTitolo(), this);
  QString autori_string = "";
  for (int i = 0; i < elemento->getAutori().size() - 1; i++) {
    autori_string += elemento->getAutori()[i] + ", ";
  }
  autori_string += elemento->getAutori().back();
  autori = new QLabel(autori_string, this);
  layout->addWidget(titolo);
  layout->addWidget(autori);
  setLayout(layout);

  elemento->registerObserver(this);
}

ProductCard::~ProductCard() {}

void ProductCard::notify(ElementoBiblioteca &elemento) {
  copertina->setPixmap(QPixmap(""));
  titolo->setText(elemento.getTitolo());
  QString autori_string = "";
  for (int i = 0; i < elemento.getAutori().size() - 1; i++) {
    autori_string += elemento.getAutori()[i] + ", ";
  }
  autori_string += elemento.getAutori().back();
  autori = new QLabel(autori_string, this);
}
