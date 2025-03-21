#include "../../header/Body/MainView.h"
#include "../../header/MainWindow.h"
#include "../../header/UIContext.h"
#include "qobject.h"
#include "qtmetamacros.h"
#include <ctime>

MainView::MainView(QWidget *parent) : QWidget(parent) {
  UIContext::setMainView(
      this); // lo setto subito senno i contenuti sono rimasti nello stato di
             // nullptr per il mainView

  layout = new QHBoxLayout(this);
  contenuti = new ContentView(this);
  dettagli = nullptr;

  layout->addWidget(contenuti);
  setLayout(layout);

  // così quando visualizzo il dettagli, il mainView si ridimensiona; senza
  // rimpicciolirsi per poi riaddattarsi
  contenuti->setSizePolicy(QSizePolicy::MinimumExpanding,
                           QSizePolicy::MinimumExpanding);
  connect(this, &MainView::searchRequested, contenuti,
          &ContentView::updateProducts);
}

MainView::~MainView() {}

void MainView::showDetailView(ElementoBiblioteca *elemento) {
  // rimuovi dettagli precedenti
  hideDetailView();
  // mostra nuovi dettagli
  dettagli = new DetailView(elemento, this);
  layout->addWidget(dettagli);

  // resize(baseSize() + dettagli->baseSize());
  emit detailViewShown();
}

void MainView::hideDetailView() {
  if (!dettagli)
    return;
  layout->removeWidget(dettagli);
  emit detailViewHidden();
  delete dettagli;
  dettagli = nullptr;
}
