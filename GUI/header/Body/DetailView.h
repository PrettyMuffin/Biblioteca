#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qpixmap.h"
#include <QWidget>

class DetailView : public QWidget {
  Q_OBJECT
private:
  ElementoBiblioteca *elemento;

  QVBoxLayout *mainLayout;
  QLabel *copertina;
  QLabel *titolo;

public:
  DetailView(ElementoBiblioteca *elemento = nullptr, QWidget *parent = nullptr);
  ~DetailView();
};

#endif
