#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include "ProductsView.h"
#include "qboxlayout.h"
#include "qcoreapplication.h"
#include "qobject.h"
#include <QWidget>

class FilterView;

class ContentView : public QWidget {
  Q_OBJECT
private:
  QVBoxLayout *layout;
  FilterView *filtri;
  ProductsView *prodotti;

  QVector<ElementoBiblioteca *> libri();
  QVector<ElementoBiblioteca *> brani();
  QVector<ElementoBiblioteca *> film();
  QVector<ElementoBiblioteca *> query(QString = "");

public:
  ContentView(QWidget * = nullptr);
  ~ContentView();
  enum FilterType { QUERY, LIBRI, BRANI, FILM };

public slots:
  void updateProducts(FilterType, QString = "");
};

#endif
