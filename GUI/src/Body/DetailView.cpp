#include "../../header/Body/DetailView.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Body/DetailViewVisitor.h"
#include "../../header/Body/EditViewVisitor.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"

#include "qabstractbutton.h"
#include "qboxlayout.h"
#include "qlayoutitem.h"
#include "qmessagebox.h"
#include "qobject.h"
#include "qsizepolicy.h"
#include "qstackedwidget.h"
#include "qwidget.h"
#include <QHBoxLayout>
#include <QPushButton>

DetailView::DetailView(ElementoBiblioteca *el, QWidget *parent)
    : QWidget(parent), elemento(el) {
  QHBoxLayout *mainLayout = new QHBoxLayout(this);

  layoutContainer = new QStackedWidget(this);
  detailWidget = new QWidget(layoutContainer);
  editWidget = new QWidget(layoutContainer);
  detailLayout = new QVBoxLayout(detailWidget);
  editLayout = new QVBoxLayout(editWidget);
  layoutContainer->addWidget(detailWidget);
  layoutContainer->addWidget(editWidget);

  detailView = new DetailViewVisitor();
  editView = new EditViewVisitor();
  el->accept(detailView);
  el->accept(editView);

  detailLayout->addWidget(detailView->getWidget());
  editLayout->addWidget(editView->getWidget());

  mainLayout->addWidget(layoutContainer);
  layoutContainer->setCurrentIndex(DETAIL_LAYOUT);

  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

  connect(detailView, &DetailViewVisitor::chiudi, UIContext::getMainView(),
          &MainView::hideDetailView);
  connect(detailView, &DetailViewVisitor::elimina, this,
          [this]() { deleteElement(elemento); });
  connect(detailView, &DetailViewVisitor::modifica, this,
          [this]() { layoutContainer->setCurrentIndex(EDIT_LAYOUT); });
  connect(editView, &EditViewVisitor::annulla, this,
          [this]() { layoutContainer->setCurrentIndex(DETAIL_LAYOUT); });
  connect(editView, &EditViewVisitor::modifica, this, &DetailView::editElement);
}

// faccio anche hidedetailview
void DetailView::deleteElement(ElementoBiblioteca *elemento) {
  QMessageBox *conferma = new QMessageBox(this);
  conferma->setText("Sicuro di voler eliminare l'elemento?");
  QAbstractButton *si = conferma->addButton("Si", QMessageBox::AcceptRole);
  conferma->addButton("No", QMessageBox::RejectRole);
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

void DetailView::editRequest() { layoutContainer->setCurrentIndex(1); }

void DetailView::editElement(ElementoBiblioteca *new_el) {
  if (AppContext::getBiblioteca()->update(elemento, new_el)) {
    sendFeedback("Elemento aggiornato con successo");
    MainView *parente = dynamic_cast<MainView *>(parent());
    if (parente)
      parente->hideDetailView();
    return;
  }
}

void DetailView::sendFeedback(QString feedback_str) {
  feedback = new QMessageBox();
  feedback->setText(feedback_str);
  feedback->exec();
}
