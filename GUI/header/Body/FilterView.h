#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include <QWidget>

class FilterView : public QWidget {
  Q_OBJECT
private:
  QVBoxLayout *layout;
  QLabel *info;
  QHBoxLayout *bottoniLayout;
  QPushButton *libroFilter;
  QPushButton *branoFilter;
  QPushButton *filmFilter;

public:
  FilterView(QWidget * = nullptr);
  ~FilterView();
};

#endif
