#include "../../header/Body/ContentView.h"

ContentView::ContentView(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);

  filtri = new FilterView(this);
  prodotti = new ProductsView(this);

  layout->addWidget(filtri);
  layout->addWidget(prodotti);

  setLayout(layout);
}

ContentView::~ContentView() {
  delete filtri;
  delete prodotti;
}
