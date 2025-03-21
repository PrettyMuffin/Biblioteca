#include "../../header/Body/ProductCard.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qlabel.h"
#include "qpixmap.h"
#include <QMouseEvent>

ProductCard::ProductCard(ElementoBiblioteca *elemento, QWidget *parent)
    : QWidget(parent), elemento(elemento) {
  layout = new QVBoxLayout(this);
  copertina = new QLabel("", this);
  titolo = new QLabel(elemento->getTitolo(), this);
  QString autori_string = "";
  for (int i = 0; i < elemento->getAutori().size() - 1; i++) {
    autori_string += elemento->getAutori()[i] + ", ";
  }
  autori_string += elemento->getAutori().back();
  autori = new QLabel(autori_string, this);
  layout->addWidget(titolo);
  layout->addWidget(autori);
  setLayout(layout);

  elemento->registerObserver(this);

  connect(this, &ProductCard::clicked, UIContext::getMainView(),
          &MainView::showDetailView);

  setMinimumSize(QSize(50, 100));
}

ProductCard::~ProductCard() {
  delete layout;
  delete copertina;
  delete titolo;
  delete autori;
}

void ProductCard::notify(ElementoBiblioteca &elemento) {
  copertina->setPixmap(QPixmap(""));
  titolo->setText(elemento.getTitolo());
  QString autori_string = "";
  for (int i = 0; i < elemento.getAutori().size() - 1; i++) {
    autori_string += elemento.getAutori()[i] + ", ";
  }
  autori_string += elemento.getAutori().back();
  autori = new QLabel(autori_string, this);
}

void ProductCard::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit clicked(elemento);
  }
}
