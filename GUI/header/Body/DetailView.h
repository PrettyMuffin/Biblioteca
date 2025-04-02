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
#include "qpropertyanimation.h"
#include "qpushbutton.h"
#include "qstackedwidget.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QGraphicsOpacityEffect>
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
  enum LayoutIndex { DETAIL_LAYOUT, EDIT_LAYOUT };

  DetailViewVisitor *detailView;
  EditViewVisitor *editView;
  ElementoBiblioteca *elemento;

  QMessageBox *feedback;

  void sendFeedback(QString);

public slots:
  void editElement(ElementoBiblioteca *);
  void deleteElement(ElementoBiblioteca *elemento);
  void editRequest();

public:
  DetailView(ElementoBiblioteca *elemento = nullptr, QWidget *parent = nullptr);
  ~DetailView();
  // void showWithAnimation(); // Mostra con animazione
  // void hideWithAnimation(); // Nascondi con animazione
};

#endif
