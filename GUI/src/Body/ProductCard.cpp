#include "../../header/Body/ProductCard.h"
#include "../../header/Body/MainView.h"
#include "../../header/UIContext.h"
#include "qboxlayout.h"
#include "qevent.h"
#include "qlabel.h"
#include "qnamespace.h"
#include "qpixmap.h"
#include "qwidget.h"
#include <QMouseEvent>

ProductCard::ProductCard(ElementoBiblioteca *elemento, QWidget *parent)
    : QWidget(parent), elemento(elemento) {
  layout = new QVBoxLayout(this);
  copertina = new QLabel(this);
  copertina->setStyleSheet("border-radius: 10px;");
  QWidget *info = new QWidget(this);
  QVBoxLayout *layoutinfo = new QVBoxLayout(info);
  titolo = new QLabel(elemento->getTitolo(), this);
  autori = new QLabel(elemento->getAutori().join(", "), this);
  layoutinfo->addWidget(titolo);
  layoutinfo->addWidget(autori);
  layout->addWidget(copertina);
  layout->addWidget(info);
  setLayout(layout);
  QPixmap pixmap = QPixmap(elemento->getImmagine());
  pixmap = pixmap.scaled(170, 250, Qt::KeepAspectRatio);
  copertina->setPixmap(pixmap);

  elemento->registerObserver(this);

  connect(this, &ProductCard::clicked, UIContext::getMainView(),
          &MainView::showDetailView);

  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ProductCard::~ProductCard() { elemento->unregisterObserver(this); }

void ProductCard::notify(ElementoBiblioteca &elemento) {
  QPixmap pixmap = QPixmap(elemento.getImmagine());
  pixmap = pixmap.scaled(170, 250, Qt::KeepAspectRatio);
  copertina->setPixmap(pixmap);
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

void ProductCard::enterEvent(QEnterEvent *event) {
  QWidget::enterEvent(event);
  setCursor(Qt::PointingHandCursor);
}

void ProductCard::leaveEvent(QEvent *event) {
  QWidget::leaveEvent(event);
  setCursor(Qt::ArrowCursor);
}
