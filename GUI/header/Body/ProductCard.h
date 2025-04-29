#ifndef PRODUCTCARD_H
#define PRODUCTCARD_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include <QWidget>

class ProductCard : public QWidget, public ElementoBibliotecaObserver {
  Q_OBJECT
  friend bool operator==(const ProductCard &lhs, const ProductCard &rhs);

protected:
  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;

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

bool operator==(const ProductCard &lhs, const ProductCard &rhs);
#endif
