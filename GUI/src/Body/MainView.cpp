#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"

MainView::MainView(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout(this);
  contenuti = new ContentView(this);
  // dettagli = new DetailView(this);

  layout->addWidget(contenuti);
  // layout->addWidget(dettagli);

  // dettagli->setHidden(true); // pk non ci sono elementi selezionati

  setLayout(layout);
  UIContext::setMainView(this);
}

MainView::~MainView() {}

void MainView::showDetailView(ElementoBiblioteca *elemento) {
  dettagli = new DetailView(elemento, this);
  layout->addWidget(dettagli);
}
