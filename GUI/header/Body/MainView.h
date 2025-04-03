#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "ContentView.h"
#include "DetailView.h"
#include "FilterView.h"
#include "ProductsView.h"
#include "qboxlayout.h"
#include "qinputdevice.h"
#include "qlineedit.h"
#include "qlist.h"
#include "qspinbox.h"
#include "qtextedit.h"
#include "qtmetamacros.h"
#include "qwidget.h"
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
  void updateViewRequested();
  void clear();

public:
  MainView(QWidget * = nullptr);
  ~MainView();
};

#endif
