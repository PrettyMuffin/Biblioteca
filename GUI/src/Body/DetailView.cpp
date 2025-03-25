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
  editView = new EditViewVisitor();
  el->accept(detailView);
  el->accept(editView);

  initDetailView(detailView);
  initEditView(editView);

  QHBoxLayout *a = new QHBoxLayout();
  a->addWidget(layoutContainer);
  setLayout(a);
  layoutContainer->setCurrentIndex(0);
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
  delete detailView;
  delete editView;
}

void DetailView::initDetailView(DetailViewVisitor *visitor) {
  pulsanti_detail = new QHBoxLayout();
  modifica = new QPushButton("Modifica");
  elimina = new QPushButton("Elimina");
  chiudi = new QPushButton("Chiudi");

  pulsanti_detail->addWidget(chiudi);
  pulsanti_detail->addWidget(elimina);
  pulsanti_detail->addWidget(modifica);

  detailLayout->addWidget(visitor->getWidget());
  detailLayout->addLayout(pulsanti_detail);
  detailWidget->setLayout(detailLayout);

  connect(chiudi, &QPushButton::clicked, UIContext::getMainView(),
          &MainView::hideDetailView);

  connect(elimina, &QPushButton::clicked, this,
          [this]() { deleteRequest(elemento); });

  connect(modifica, &QPushButton::clicked, this,
          [this]() { layoutContainer->setCurrentIndex(1); });
}

void DetailView::initEditView(EditViewVisitor *visitor) {
  pulsanti_edit = new QHBoxLayout();
  salva = new QPushButton("Salva");
  annulla = new QPushButton("Annulla");
  pulsanti_edit->addWidget(annulla);
  pulsanti_edit->addWidget(salva);

  assert(visitor->getWidget() != nullptr);
  editLayout->addWidget(visitor->getWidget());
  editLayout->addLayout(pulsanti_edit);
  editWidget->setLayout(editLayout);

  connect(annulla, &QPushButton::clicked, this,
          [this]() { layoutContainer->setCurrentIndex(0); });

  // connect(salva, &QPushButton::clicked, this,
  //         [this]() { saveChanges(elemento); });
}
