#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"

MainView::MainView(QWidget *parent) : QWidget(parent) {
  UIContext::setMainView(
      this); // lo setto subito senno i contenuti sono rimasti nello stato di
             // nullptr per il mainView

  layout = new QHBoxLayout(this);
  contenuti = new ContentView(this);
  dettagli = nullptr;

  layout->addWidget(contenuti);

  setLayout(layout);
}

MainView::~MainView() {}

void MainView::showDetailView(ElementoBiblioteca *elemento) {
  // rimuovi dettagli precedenti
  hideDetailView();
  // mostra nuovi dettagli
  dettagli = new DetailView(elemento, this);
  layout->addWidget(dettagli);
}

void MainView::hideDetailView() {
  if (!dettagli)
    return;
  layout->removeWidget(dettagli);
  delete dettagli;
}
