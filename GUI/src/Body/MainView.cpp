#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qapplication.h"
#include "qframe.h"
#include "qinputdevice.h"
#include "qlineedit.h"
#include "qobject.h"
#include "qtextedit.h"
#include "qwidget.h"
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
  connect(this, &MainView::hideDetailView, this, &MainView::onHideDetailView);
  connect(this, &MainView::showDetailView, this, &MainView::onShowDetailView);
  connect(this, &MainView::deleteProductRequested, contenuti,
          &ContentView::onDeleteProduct);
  connect(this, &MainView::updateViewRequested, contenuti, [this]() {
    contenuti->updateProducts(ContentView::QUERY, "");
  }); // un cheat per ottenere tutti gli elementi della biblioteca
}

MainView::~MainView() {}

void MainView::onShowDetailView(ElementoBiblioteca *elemento) {
  // rimuovi dettagli precedenti
  onHideDetailView();
  // mostra nuovi dettagli
  dettagli = new DetailView(elemento, this);
  layout->addWidget(dettagli);
}

void MainView::onHideDetailView() {
  if (!dettagli)
    return;
  layout->removeWidget(dettagli);
  delete dettagli;
  dettagli = nullptr;
}
