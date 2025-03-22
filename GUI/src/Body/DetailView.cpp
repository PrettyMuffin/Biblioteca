#include "../../header/Body/DetailView.h"
#include "../../header/Body/DetailViewVisitor.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qabstractbutton.h"
#include "qlayout.h"
#include "qmessagebox.h"

#include <QHBoxLayout>
#include <QPushButton>

DetailView::DetailView(ElementoBiblioteca *el, QWidget *parent)
    : QWidget(parent), elemento(el) {
  DetailviewVisitor v;
  el->accept(&v);

  QHBoxLayout *pulsanti = new QHBoxLayout();
  QPushButton *modifica = new QPushButton("Modifica");
  QPushButton *elimina = new QPushButton("Elimina");
  QPushButton *chiudi = new QPushButton("Chiudi");
  pulsanti->addWidget(chiudi);
  pulsanti->addWidget(elimina);
  pulsanti->addWidget(modifica);

  QLayout *layout = v.getWidget()->layout();
  layout->addItem(pulsanti);

  setLayout(layout);

  connect(chiudi, &QPushButton::clicked, UIContext::getMainView(),
          &MainView::hideDetailView);
  connect(elimina, &QPushButton::clicked, this,
          [this]() { deleteRequest(elemento); });
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
DetailView::~DetailView() {}
