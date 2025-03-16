#include "../../header/Body/MainView.h"

MainView::MainView(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout(this);
  contenuti = new ContentView(this);
  dettagli = new DetailView(this);

  layout->addWidget(contenuti);
  layout->addWidget(dettagli);

  dettagli->setHidden(true); // pk non ci sono elementi selezionati

  setLayout(layout);
}

MainView::~MainView() {}
