#include "../../header/Body/MainView.h"
#include "../../header/MainWindow.h"
#include "../../header/UIContext.h"
#include "qtmetamacros.h"

MainView::MainView(QWidget *parent) : QWidget(parent) {
  UIContext::setMainView(
      this); // lo setto subito senno i contenuti sono rimasti nello stato di
             // nullptr per il mainView

  layout = new QHBoxLayout(this);
  contenuti = new ContentView(this);
  dettagli = nullptr;

  layout->addWidget(contenuti);

  setLayout(layout);

  MainWindow *mainWindow = dynamic_cast<MainWindow *>(parent);
  if (mainWindow) {
    connect(this, &MainView::detailViewShown, mainWindow, [mainWindow, this]() {
      // mainWindow->resize(mainWindow->frameSize() + dettagli->frameSize());
      mainWindow->adjustSize();
    });
    connect(this, &MainView::detailViewHidden, mainWindow,
            [mainWindow, this]() { mainWindow->adjustSize(); });
  }
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
}
