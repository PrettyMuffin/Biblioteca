#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "DetailViewVisitor.h"
#include "EditViewVisitor.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qpixmap.h"
#include "qpushbutton.h"
#include "qstackedwidget.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QStackedLayout>
#include <QWidget>

class DetailView : public QWidget {
  Q_OBJECT
private:
  QStackedWidget *layoutContainer;

  QWidget *detailWidget;
  QWidget *editWidget;
  QVBoxLayout *detailLayout;
  QVBoxLayout *editLayout;

  QVBoxLayout *currentLayout;

  DetailViewVisitor *detailView;
  EditViewVisitor *editView;
  ElementoBiblioteca *elemento;

  QHBoxLayout *pulsanti_detail;
  QHBoxLayout *pulsanti_edit;
  QPushButton *modifica;
  QPushButton *elimina;
  QPushButton *chiudi;
  QPushButton *salva;
  QPushButton *annulla;

  void initDetailView(DetailViewVisitor *);
  void initEditView(EditViewVisitor *);

  void deletePulsanti();

public slots:
  void deleteRequest(ElementoBiblioteca *elemento);
  void editRequest();

public:
  DetailView(ElementoBiblioteca *elemento = nullptr, QWidget *parent = nullptr);
  ~DetailView();
};

#endif
