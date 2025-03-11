#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include "qboxlayout.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

class SearchBar : public QWidget {
  Q_OBJECT
  QHBoxLayout *layout;
  QLineEdit *searchInput;
  QPushButton *searchButton; // Boh non so se farlo rimanere, vedremo

protected:
  void keyPressEvent(QKeyEvent *event) override;

public:
  SearchBar(QWidget * = nullptr);
  ~SearchBar();

signals:
  void onSearchEvent(const QString &);
};

#endif
