#ifndef DETAILVIEWVISITOR_H
#define DETAILVIEWVISITOR_H

#include "../../../Logica/header/ElementoBibliotecaVisitor.h"
#include "qlayout.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include "qwidget.h"

class DetailViewVisitor : public QWidget, public ElementoBibliotecaVisitor {
  Q_OBJECT
private:
  QWidget *widget;
  QVBoxLayout *layout;
  QHBoxLayout *pulsanti_layout;
  QPushButton *_chiudi;
  QPushButton *_elimina;
  QPushButton *_modifica;
  void initPulsanti();

signals:
  void chiudi();
  void elimina();
  void modifica();

public:
  DetailViewVisitor();
  ~DetailViewVisitor();
  void visit(Libro *) override;
  void visit(Brano *) override;
  void visit(Film *) override;
  QWidget *getWidget() const;
};

#endif
