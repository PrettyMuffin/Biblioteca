#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

class MainView : public QWidget {
  Q_OBJECT
public:
  MainView(QWidget * = nullptr);
  ~MainView();
};

#endif
