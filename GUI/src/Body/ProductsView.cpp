#include "../../header/Body/ProductsView.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Body/ProductCard.h"
#include "../../header/CursorEventFilter.h"
#include "../../header/UIContext.h"

#include "qglobal.h"
#include "qlayoutitem.h"
#include "qobject.h"
#include "qscrollarea.h"
#include "qsizepolicy.h"
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
  maxCols = 5;

  setProducts(elements);

  scrollContent->setLayout(layout);
  scrollArea->setWidget(scrollContent);
  scrollArea->setWidgetResizable(true);

  scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::MinimumExpanding);

  mainLayout->addWidget(scrollArea);
  setLayout(mainLayout);
}

void ProductsView::setProducts(QVector<ElementoBiblioteca *> elements) {
  if (!layout->isEmpty())
    UIContext::clearLayout(layout);
  if (elements.isEmpty())
    return;

  int row = 0, col = 0;
  CursorEventFilter *hover = new CursorEventFilter(this);
  for (auto elemento : elements) {
    ProductCard *card = new ProductCard(elemento, this);
    card->installEventFilter(hover);
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
      // rowspan, colspan inutili dato che tutti gli el hanno 1 di entrambi
      int row, col, rowSpan, columnSpan;
      layout->getItemPosition(i, &row, &col, &rowSpan, &columnSpan);

      QLayoutItem *item = layout->takeAt(i);
      delete p_card;
      p_card = nullptr;
      delete item;

      // ritorna sempre true, dato che vi accedo tramite
      // click di  una product card, che rappresenta tutti gli elementi presenti
      // nella biblioteca
      AppContext::getBiblioteca()->remove(elemento);

      // potevo fare un setProducts ma non mi sembrava efficiente eliminare
      // tutto per poi riaggungere tutto, specialmente se la lista è molto lunga
      // e magari elimino l'ultimo elemento
      // inoltre così se ho un risultato di una ricerca resta nel contesto della
      // ricerca
      adjustLayout(i, row, col);
      return;
    }
  }
}

/**
 * @param start l'indice di partenza da cui iniziare a risistemare il layout.
 * @param row_start_el l'indice di riga dell'elemento di partenza.
 * @param col_start_el l'indice di colonne dell'elemento di partenza.
 */
void ProductsView::adjustLayout(int start, int row_start_el, int col_start_el) {
  QList<QWidget *> widgets;
  while (QLayoutItem *item = layout->takeAt(start)) {
    if (QWidget *widget = item->widget()) {
      widgets.append(widget);
    }
    delete item;
  }
  for (int j = 0; j < widgets.count(); j++) {
    layout->addWidget(widgets[j], row_start_el, col_start_el);
    col_start_el++;
    if (col_start_el >= maxCols) {
      col_start_el = 0;
      row_start_el++;
    }
  }
}

ProductsView::~ProductsView() { delete layout; }
