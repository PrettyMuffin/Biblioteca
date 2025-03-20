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
  void showDetailView(ElementoBiblioteca *);
  void hideDetailView();

signals:
  void detailViewShown();
  void detailViewHidden();

public:
  MainView(QWidget * = nullptr);
  ~MainView();
};

#endif
