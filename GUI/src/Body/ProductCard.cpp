#include "../../header/Body/ProductCard.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qpixmap.h"
#include "qwidget.h"
#include <QMouseEvent>

ProductCard::ProductCard(ElementoBiblioteca *elemento, QWidget *parent)
    : QWidget(parent), elemento(elemento) {
  layout = new QVBoxLayout(this);
  copertina = new QLabel(this);
  copertina->setPixmap(QPixmap(elemento->getImmagine()));
  QWidget *info = new QWidget(this);
  info->setStyleSheet("background-color: #536cc1;");
  QVBoxLayout *layoutinfo = new QVBoxLayout(info);
  titolo = new QLabel(elemento->getTitolo(), this);
  autori = new QLabel(elemento->getAutori().join(", "), this);
  layoutinfo->addWidget(titolo);
  layoutinfo->addWidget(autori);
  layout->addWidget(copertina);
  layout->addWidget(info);
  setLayout(layout);

  elemento->registerObserver(this);

  connect(this, &ProductCard::clicked, UIContext::getMainView(),
          &MainView::showDetailView);

  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

ProductCard::~ProductCard() { elemento->unregisterObserver(this); }

void ProductCard::notify(ElementoBiblioteca &elemento) {
  copertina->setPixmap(QPixmap(""));
  titolo->setText(elemento.getTitolo());
  autori->setText(elemento.getAutori().join(","));
}

void ProductCard::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit clicked(elemento);
  }
}

bool operator==(const ProductCard &lhs, const ProductCard &rhs) {
  return lhs.elemento == rhs.elemento;
}
