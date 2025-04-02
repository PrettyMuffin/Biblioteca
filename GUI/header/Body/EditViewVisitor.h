#ifndef EDITVIEWVISITOR_H
#define EDITVIEWVISITOR_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qboxlayout.h"
#include "qcoreapplication.h"
#include "qhashfunctions.h"
#include "qlist.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include "qwidget.h"

class EditViewVisitor : public QWidget, public ElementoBibliotecaVisitor {
  Q_OBJECT
private:
  QString newPath;
  QWidget *widget;
  QHBoxLayout *pulsanti_layout;
  QVBoxLayout *layout;
  QPushButton *_annulla;
  QPushButton *_modifica;
  void initPulsanti();

signals:
  void modifica(
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
