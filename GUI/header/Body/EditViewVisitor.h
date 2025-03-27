#ifndef EDITVIEWVISITOR_H
#define EDITVIEWVISITOR_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qboxlayout.h"
#include "qlist.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include "qwidget.h"

class EditViewVisitor : public QWidget, public ElementoBibliotecaVisitor {
  Q_OBJECT
private:
  QWidget *widget;
  QVBoxLayout *layout;

  QHBoxLayout *pulsanti_layout;
  QPushButton *_annulla;
  QPushButton *_salva;

  void initPulsanti();

signals:
  void salva(
      ElementoBiblioteca *); // lista di stringhe con i parametri dell'elemento
  void annulla();

public:
  EditViewVisitor();
  ~EditViewVisitor();
  void visit(Libro *) override;
  void visit(Brano *) override;
  void visit(Film *) override;
  QWidget *getWidget();
};

#endif
