#ifndef PRODUCTCARD_H
#define PRODUCTCARD_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include <QWidget>

class ProductCard : public QWidget, public ElementoBibliotecaObserver {
  Q_OBJECT
private:
  QVBoxLayout *layout;
  QLabel *copertina;
  QLabel *titolo;
  QLabel *autori;
  ElementoBiblioteca *elemento;

private:
  void mousePressEvent(QMouseEvent *event) override;

signals:
  void clicked(ElementoBiblioteca *);

public:
  ProductCard(ElementoBiblioteca *, QWidget * = nullptr);
  void notify(ElementoBiblioteca &) override;
  ~ProductCard();
};
#endif
