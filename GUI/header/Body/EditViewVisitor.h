#ifndef EDITVIEWVISITOR_H
#define EDITVIEWVISITOR_H

#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qobject.h"
#include "qtmetamacros.h"
#include "qwidget.h"

class EditViewVisitor : public QWidget, public ElementoBibliotecaVisitor {
  Q_OBJECT
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
