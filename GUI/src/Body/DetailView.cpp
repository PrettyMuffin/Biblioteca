#include "../../header/Body/DetailView.h"
#include "../../header/Body/DetailViewVisitor.h"
#include "../../header/Body/EditViewVisitor.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qabstractbutton.h"
#include "qboxlayout.h"
#include "qglobal.h"
#include "qlayoutitem.h"
#include "qmessagebox.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qstackedwidget.h"
#include "qwidget.h"

#include <QHBoxLayout>
#include <QPushButton>

DetailView::DetailView(ElementoBiblioteca *el, QWidget *parent)
    : QWidget(parent), elemento(el) {
  layoutContainer = new QStackedWidget(this);
  detailWidget = new QWidget(this);
  editWidget = new QWidget(this);
  detailLayout = new QVBoxLayout(detailWidget);
  editLayout = new QVBoxLayout(editWidget);
  layoutContainer->addWidget(detailWidget);
  layoutContainer->addWidget(editWidget);

  detailView = new DetailViewVisitor();
  editView = new EditViewVisitor;
  el->accept(detailView);
  el->accept(editView);

  // currentLayout = new QVBoxLayout(this);

  initDetailView(detailView);
  initEditView(editView);
  QHBoxLayout *a = new QHBoxLayout();
  a->addWidget(layoutContainer);
  setLayout(a);
  layoutContainer->setCurrentIndex(0);
  // mainLayout->addWidget(currentWidget);
}

// faccio anche hidedetailview
void DetailView::deleteRequest(ElementoBiblioteca *elemento) {
  QMessageBox *conferma = new QMessageBox(this);
  conferma->setText("Sicuro di voler eliminare l'elemento?");
  QAbstractButton *si = conferma->addButton("Si", QMessageBox::AcceptRole);
  QAbstractButton *no = conferma->addButton("No", QMessageBox::RejectRole);
  conferma->exec();
  if (conferma->clickedButton() == si) {
    UIContext::getMainView()->hideDetailView();
    emit(UIContext::getMainView()->deleteProductRequested(elemento));
  }
}

void DetailView::editRequest() { initEditView(editView); }

// non faccio delete *elemento pk sennò lo eliminerei dalla biblioteca,
DetailView::~DetailView() {
  delete currentLayout;
  delete pulsanti;
  delete modifica;
  delete elimina;
  delete chiudi;
  delete salva;
  delete detailView;
  delete editView;
}

void DetailView::initDetailView(DetailViewVisitor *visitor) {
  UIContext::clearLayout(currentLayout);
  pulsanti = new QHBoxLayout();
  modifica = new QPushButton("Modifica");
  elimina = new QPushButton("Elimina");
  chiudi = new QPushButton("Chiudi");

  pulsanti->addWidget(chiudi);
  pulsanti->addWidget(elimina);
  pulsanti->addWidget(modifica);

  detailLayout->addWidget(visitor->getWidget());
  detailLayout->addLayout(pulsanti);
  detailWidget->setLayout(detailLayout);

  connect(chiudi, &QPushButton::clicked, UIContext::getMainView(),
          &MainView::hideDetailView);

  connect(elimina, &QPushButton::clicked, this,
          [this]() { deleteRequest(elemento); });

  connect(modifica, &QPushButton::clicked, this, [this]() { editRequest(); });
}

void DetailView::initEditView(EditViewVisitor *visitor) {
  UIContext::clearLayout(currentLayout);
  pulsanti = new QHBoxLayout();
  salva = new QPushButton("Salva");
  chiudi = new QPushButton("Annulla");
  pulsanti->addWidget(chiudi);
  pulsanti->addWidget(salva);

  editLayout->addWidget(visitor->getWidget());
  editLayout->addLayout(pulsanti);
  editWidget->setLayout(editLayout);

  connect(chiudi, &QPushButton::clicked, this, [this]() {
    qDebug() << (detailView == nullptr);
    initDetailView(detailView);
  });

  // connect(salva, &QPushButton::clicked, this,
  //         [this]() { saveChanges(elemento); });
}
