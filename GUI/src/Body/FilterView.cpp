#include "../../header/Body/FilterView.h"
#include "../../header/Body/ContentView.h"
#include "qwidget.h"

FilterView::FilterView(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  info = new QLabel("Cerca nella biblioteca", this);
  bottoniLayout = new QHBoxLayout;
  tuttiFilter = new QPushButton("Tutti", this);
  libroFilter = new QPushButton("Libro", this);
  branoFilter = new QPushButton("Brano", this);
  filmFilter = new QPushButton("Film", this);

  bottoniLayout->addWidget(tuttiFilter);
  bottoniLayout->addWidget(libroFilter);
  bottoniLayout->addWidget(branoFilter);
  bottoniLayout->addWidget(filmFilter);

  layout->addWidget(info);
  layout->addLayout(bottoniLayout);

  setLayout(layout);

  connect(tuttiFilter, &QPushButton::clicked, this,
          [this]() { emit filterChanged(ContentView::QUERY); });
  connect(libroFilter, &QPushButton::clicked, this,
          [this]() { emit filterChanged(ContentView::LIBRI); });
  connect(branoFilter, &QPushButton::clicked, this,
          [this]() { emit filterChanged(ContentView::BRANI); });
  connect(filmFilter, &QPushButton::clicked, this,
          [this]() { emit filterChanged(ContentView::FILM); });
}

FilterView::~FilterView() {}
