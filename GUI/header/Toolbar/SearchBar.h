#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include "qboxlayout.h"
#include "qpushbutton.h"
#include <QLineEdit>
#include <QWidget>

class SearchBar : public QWidget {
  Q_OBJECT
  QHBoxLayout *layout;
  QLineEdit *searchInput;
  QPushButton *searchButton; // Boh non so se farlo rimanere, vedremo

public:
  SearchBar(QWidget *parent = nullptr);
  ~SearchBar();
};

#endif
