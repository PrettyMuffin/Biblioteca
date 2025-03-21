#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include "../../header/Body/ContentView.h"
#include "qboxlayout.h"
#include "qcoreapplication.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include <QWidget>

class FilterView : public QWidget {
Q_OBJECT private : QVBoxLayout *layout;
  QLabel *info;
  QHBoxLayout *bottoniLayout;
  QPushButton *libroFilter;
  QPushButton *branoFilter;
  QPushButton *filmFilter;
  QPushButton *tuttiFilter;

public:
  FilterView(QWidget * = nullptr);
  ~FilterView();

signals:
  void filterChanged(ContentView::FilterType, const QString & = "");
};

#endif
