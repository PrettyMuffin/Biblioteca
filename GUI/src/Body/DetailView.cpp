#include "../../header/Body/DetailView.h"
#include "qlabel.h"

DetailView::DetailView(ElementoBiblioteca *el, QWidget *parent)
    : QWidget(parent), elemento(el) {
  mainLayout = new QVBoxLayout(this);
  titolo = new QLabel(el->getTitolo(), this);
  copertina = new QLabel(this);
  mainLayout->addWidget(titolo);
  mainLayout->addWidget(copertina);
  setLayout(mainLayout);
}

DetailView::~DetailView() {}
