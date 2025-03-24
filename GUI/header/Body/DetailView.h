#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "DetailViewVisitor.h"
#include "EditViewVisitor.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qpixmap.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QStackedWidget>
#include <QWidget>

class DetailView : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *mainLayout;
  QStackedWidget *container;
  QWidget *currentWidget;
  QVBoxLayout *currentLayout;

  DetailViewVisitor *detailView;
  EditViewVisitor *editView;
  ElementoBiblioteca *elemento;

  void initDetailView(DetailViewVisitor *);
  void initEditView(EditViewVisitor *);

public slots:
  void deleteRequest(ElementoBiblioteca *elemento);

public:
  DetailView(ElementoBiblioteca *elemento = nullptr, QWidget *parent = nullptr);
  ~DetailView();
};

#endif
