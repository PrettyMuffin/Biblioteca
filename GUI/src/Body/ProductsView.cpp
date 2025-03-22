#include "../../header/Body/ProductsView.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Body/ProductCard.h"
#include "qdebug.h"
#include "qlayoutitem.h"

#include "qlogging.h"
#include "qobject.h"
#include "qscrollarea.h"
#include "qwidget.h"
#include <QMouseEvent>
#include <cstdlib>

ProductsView::ProductsView(QVector<ElementoBiblioteca *> elements,
                           QWidget *parent)
    : QWidget(parent) {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  scrollArea = new QScrollArea(this);
  QWidget *scrollContent = new QWidget(scrollArea);

  layout = new QGridLayout(scrollContent);
  maxCols = 6;

  setProducts(elements);

  scrollContent->setLayout(layout);
  scrollArea->setWidget(scrollContent);
  scrollArea->setWidgetResizable(true);
  scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  mainLayout->addWidget(scrollArea);
  setLayout(mainLayout);
}

void ProductsView::setProducts(QVector<ElementoBiblioteca *> elements) {
  if (!layout->isEmpty())
    clearLayout();
  if (elements.isEmpty())
    return;
  int row = 0, col = 0;
  for (auto elemento : elements) {
    ProductCard *card = new ProductCard(elemento, this);
    layout->addWidget(card, row, col);

    // int maxCols = frameSize().width() / card->minimumSize().width();
    col++;
    if (col >= maxCols) {
      col = 0;
      row++;
    }
  }
}

void ProductsView::clearLayout() {
  while (QLayoutItem *item = layout->takeAt(0)) {
    layout->removeWidget(item->widget());
    delete item->widget();
    delete item;
  }
}

void ProductsView::deleteProduct(ElementoBiblioteca *elemento) {
  for (int i = 0; i < layout->count(); i++) {
    ProductCard *p_card =
        qobject_cast<ProductCard *>(layout->itemAt(i)->widget());
    if (p_card && *p_card == elemento) {
      QLayoutItem *item = layout->takeAt(i);
      delete p_card;
      p_card = nullptr;
      delete item;

      // ritorna sempre true, dato che vi accedo tramite
      // click di  una product card, che rappresenta tutti gli elementi presenti
      // nella biblioteca
      AppContext::getBiblioteca()->remove(elemento);

      return;
    }
  }
}

ProductsView::~ProductsView() { delete layout; }
