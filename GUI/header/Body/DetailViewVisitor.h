#ifndef DETAILVIEWVISITOR_H
#define DETAILVIEWVISITOR_H

#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qwidget.h"

class DetailViewVisitor : public ElementoBibliotecaVisitor {
private:
  QWidget *widget;

public:
  DetailViewVisitor();
  ~DetailViewVisitor();
  void visit(Libro *) override;
  void visit(Brano *) override;
  void visit(Film *) override;
  QWidget *getWidget() const;
};

#endif
