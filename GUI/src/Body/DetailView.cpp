#include "../../header/Body/DetailView.h"
#include "../../header/Body/DetailViewVisitor.h"

DetailView::DetailView(ElementoBiblioteca *el, QWidget *parent)
    : QWidget(parent), elemento(el) {
  DetailviewVisitor v;
  el->accept(&v);
  setLayout(v.getWidget()->layout());
}

// non faccio delete *elemento pk sennò lo eliminerei dalla biblioteca,
DetailView::~DetailView() {}
