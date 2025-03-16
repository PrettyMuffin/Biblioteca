#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Body/AddView.h"
#include "Body/MainView.h"
#include "Toolbar/ToolBar.h"
#include "qboxlayout.h"
#include <QStackedWidget>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT
private:
  QVBoxLayout *layout;
  Toolbar *toolbar;
  QStackedWidget *body;
  MainView *mainView;
  AddView *addView;

public:
  MainWindow(QWidget * = nullptr);
  ~MainWindow();

public slots:
  void changePage(int);
};

#endif
