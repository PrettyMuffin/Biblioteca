#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "qlabel.h"
#include "qpixmap.h"
#include <QWidget>

class DetailView : public QWidget {
  Q_OBJECT
private:
  QPixmap *copertina;

public:
  DetailView(QWidget *parent = nullptr);
  ~DetailView();
};

#endif
