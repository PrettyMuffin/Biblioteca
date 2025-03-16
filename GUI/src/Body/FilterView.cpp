#include "../../header/Body/FilterView.h"
#include "qwidget.h"

FilterView::FilterView(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  info = new QLabel("Cerca nella biblioteca", this);
  bottoniLayout = new QHBoxLayout(this);
  libroFilter = new QPushButton("Libro", this);
  branoFilter = new QPushButton("Brano", this);
  filmFilter = new QPushButton("Film", this);

  bottoniLayout->addWidget(libroFilter);
  bottoniLayout->addWidget(branoFilter);
  bottoniLayout->addWidget(filmFilter);

  layout->addWidget(info);
  layout->addLayout(bottoniLayout);

  setLayout(layout);
}

FilterView::~FilterView() {}
