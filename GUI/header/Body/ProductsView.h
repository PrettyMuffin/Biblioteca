#ifndef PRODUCTS_VIEW_H
#define PRODUCTS_VIEW_H

#include "../../../Logica/header/ElementoBiblioteca.h"
#include "qboxlayout.h"
#include "qgridlayout.h"
#include "qlabel.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QScrollArea>
#include <QWidget>

class MainView;

class ProductsView : public QWidget {
  Q_OBJECT

  friend class ProductCard; // dato che non è possibile innestare 2 oggetti con
                            // Q_OBJECT
private:
  QScrollArea *scrollArea;
  QGridLayout *layout;
  void prova();

public:
  ProductsView(QWidget * = nullptr, MainView * = nullptr);
  ~ProductsView();
};

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
