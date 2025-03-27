#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "DetailViewVisitor.h"
#include "EditViewVisitor.h"
#include "qboxlayout.h"
#include "qcoreapplication.h"
#include "qdialog.h"
#include "qlabel.h"
#include "qmessagebox.h"
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

  QMessageBox *feedback;

  void initDetailView(DetailViewVisitor *);
  void initEditView(EditViewVisitor *);
  void deletePulsanti();
  void sendFeedback(QString);

public slots:
  void saveChanges(ElementoBiblioteca *);
  void deleteRequest(ElementoBiblioteca *elemento);
  void editRequest();

public:
  DetailView(ElementoBiblioteca *elemento = nullptr, QWidget *parent = nullptr);
  ~DetailView();
};

#endif
