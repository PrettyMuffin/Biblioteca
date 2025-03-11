#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Options.h"
#include "SearchBar.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QHBoxLayout>
#include <QLabel>

class Toolbar : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *layout;
  QLabel *logo;
  SearchBar ricerca;
  Options opzioni;

public:
  Toolbar(QWidget * = nullptr);
  ~Toolbar();
};

#endif
