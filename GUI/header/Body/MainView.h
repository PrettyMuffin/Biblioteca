#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "FilterView.h"
#include "ProductsView.h"
#include "qboxlayout.h"
#include <QWidget>

class MainView : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *layout;

public:
  MainView(QWidget * = nullptr);
  ~MainView();
};

#endif
