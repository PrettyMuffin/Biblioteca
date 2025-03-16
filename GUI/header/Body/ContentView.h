#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include "FilterView.h"
#include "ProductsView.h"
#include "qboxlayout.h"
#include <QWidget>

class ContentView : public QWidget {
  Q_OBJECT
private:
  QVBoxLayout *layout;
  FilterView *filtri;
  ProductsView *prodotti;

public:
  ContentView(QWidget * = nullptr);
  ~ContentView();
};

#endif
