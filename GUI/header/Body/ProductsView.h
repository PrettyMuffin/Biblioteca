#ifndef PRODUCTS_VIEW_H
#define PRODUCTS_VIEW_H

#include "qgridlayout.h"
#include "qtmetamacros.h"
#include <QWidget>

class ProductsView : public QGridLayout {
private:
public:
  ProductsView(QWidget * = nullptr);
  ~ProductsView();
};

#endif
