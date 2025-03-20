#include "../../header/Body/ProductsView.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qcoreapplication.h"
#include "qglobal.h"
#include "qlabel.h"
#include "qpixmap.h"
#include "qscrollarea.h"
#include "qwidget.h"
#include <QMouseEvent>
#include <cstdlib>

ProductsView::ProductsView(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  scrollArea = new QScrollArea(this);
  QWidget *scrollContent = new QWidget(scrollArea);

  layout = new QGridLayout(scrollContent);

  Biblioteca *biblioteca = AppContext::getBiblioteca();
  int row = 0, col = 0;
  int maxCols = 5;
  for (auto elemento : biblioteca->getElements()) {
    ProductCard *card = new ProductCard(elemento, this);
    layout->addWidget(card, row, col);

    col++;
    if (col >= maxCols) {
      col = 0;
      row++;
    }
  }
  scrollContent->setLayout(layout);
  scrollArea->setWidget(scrollContent);
  scrollArea->setWidgetResizable(true);
  scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  mainLayout->addWidget(scrollArea);
  setLayout(mainLayout);
}

ProductsView::~ProductsView() { delete layout; }

ProductCard::ProductCard(ElementoBiblioteca *elemento, QWidget *parent)
    : QWidget(parent), elemento(elemento) {
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

  connect(this, &ProductCard::clicked, UIContext::getMainView(),
          &MainView::showDetailView);
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

void ProductCard::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit clicked(elemento);
  }
}
