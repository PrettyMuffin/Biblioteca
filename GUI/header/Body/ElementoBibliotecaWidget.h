#ifndef ELEMENTOBIBLIOTECAWIDGET_H
#define ELEMENTOBIBLIOTECAWIDGET_H

#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qwidget.h"

class ElementoBibliotecaWidget : public ElementoBibliotecaVisitor {
private:
  QWidget *widget;

public:
  ElementoBibliotecaWidget();
  ~ElementoBibliotecaWidget();
  void visit(Libro *) override;
  void visit(Brano *) override;
  void visit(Film *) override;
  QWidget *getWidget() const;
};

#endif
