#ifndef PRODUCTS_VIEW_H
#define PRODUCTS_VIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "qboxlayout.h"
#include "qgridlayout.h"
#include "qlabel.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QScrollArea>
#include <QWidget>

class MainView;

class ProductsView : public QWidget {
  Q_OBJECT

  friend class ProductCard; // dato che non è possibile innestare 2 oggetti con
                            // Q_OBJECT
private:
  QScrollArea *scrollArea;
  QGridLayout *layout;
  int maxCols;
  void clearLayout();

public:
  ProductsView(QVector<ElementoBiblioteca *>, QWidget * = nullptr);
  void setProducts(QVector<ElementoBiblioteca *>);
  ~ProductsView();
};

#endif
