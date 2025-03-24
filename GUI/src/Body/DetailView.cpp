#include "../../header/Body/DetailView.h"
#include "../../header/Body/DetailViewVisitor.h"
#include "../../header/Body/EditViewVisitor.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qabstractbutton.h"
#include "qboxlayout.h"
#include "qmessagebox.h"
#include "qobject.h"
#include "qstackedwidget.h"
#include "qwidget.h"

#include <QHBoxLayout>
#include <QPushButton>

DetailView::DetailView(ElementoBiblioteca *el, QWidget *parent)
    : QWidget(parent), elemento(el) {
  mainLayout = new QHBoxLayout(this);
  container = new QStackedWidget(this);
  currentWidget = new QWidget(this);
  currentLayout = new QVBoxLayout(currentWidget);
  currentWidget->setLayout(currentLayout);

  detailView = new DetailViewVisitor();
  editView = new EditViewVisitor;
  el->accept(detailView);
  el->accept(editView);

  initDetailView(detailView);

  mainLayout->addWidget(container);
  // setLayout(layout);
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

// non faccio delete *elemento pk sennò lo eliminerei dalla biblioteca,
DetailView::~DetailView() {
  delete detailView;
  delete editView;
}

void DetailView::initDetailView(DetailViewVisitor *visitor) {

  QWidget *visitorWidget = visitor->getWidget();

  QHBoxLayout *pulsanti = new QHBoxLayout();
  QPushButton *modifica = new QPushButton("Modifica");
  QPushButton *elimina = new QPushButton("Elimina");
  QPushButton *chiudi = new QPushButton("Chiudi");
  pulsanti->addWidget(chiudi);
  pulsanti->addWidget(elimina);
  pulsanti->addWidget(modifica);

  currentLayout->addWidget(visitor->getWidget());
  currentLayout->addLayout(pulsanti);

  connect(chiudi, &QPushButton::clicked, UIContext::getMainView(),
          &MainView::hideDetailView);

  connect(elimina, &QPushButton::clicked, this,
          [this]() { deleteRequest(elemento); });

  container->addWidget(currentWidget);
  // container->setCurrentIndex(0);
}

void DetailView::initEditView(EditViewVisitor *visitor) {}
