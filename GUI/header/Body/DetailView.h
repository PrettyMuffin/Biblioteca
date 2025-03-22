#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qpixmap.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QWidget>

class DetailView : public QWidget {
  Q_OBJECT
private:
  ElementoBiblioteca *elemento;

public slots:
  void deleteRequest(ElementoBiblioteca *elemento);

public:
  DetailView(ElementoBiblioteca *elemento = nullptr, QWidget *parent = nullptr);
  ~DetailView();
};

#endif
