#include "../../header/Body/ContentView.h"

ContentView::ContentView(QWidget *parent) : QWidget(parent) {
  filtri = new FilterView(this);
  prodotti = new ProductsView(this);
}

ContentView::~ContentView() {
  delete filtri;
  delete prodotti;
}
