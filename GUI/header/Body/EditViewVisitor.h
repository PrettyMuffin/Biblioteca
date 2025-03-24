#ifndef EDITVIEWVISITOR_H
#define EDITVIEWVISITOR_H

#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qwidget.h"

class EditViewVisitor : public ElementoBibliotecaVisitor {
private:
  QWidget *widget;

public:
  EditViewVisitor();
  ~EditViewVisitor();
  void visit(Libro *) override;
  void visit(Brano *) override;
  void visit(Film *) override;
  QWidget *getWidget();
};

#endif
