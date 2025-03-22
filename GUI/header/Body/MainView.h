#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "ContentView.h"
#include "DetailView.h"
#include "FilterView.h"
#include "ProductsView.h"
#include "qboxlayout.h"
#include "qtmetamacros.h"
#include <QWidget>

class MainView : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *layout;
  ContentView *contenuti;
  DetailView *dettagli;

public slots:
  void onShowDetailView(ElementoBiblioteca *);
  void onHideDetailView();

signals:
  void showDetailView(ElementoBiblioteca *);
  void hideDetailView();
  void deleteProductRequested(ElementoBiblioteca *);
  void searchRequested(ContentView::FilterType, const QString &);

public:
  MainView(QWidget * = nullptr);
  ~MainView();
};

#endif
