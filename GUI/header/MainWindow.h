#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Body/AddView.h"
#include "Body/MainView.h"
#include "Toolbar/ToolBar.h"
#include "qboxlayout.h"
#include "qtmetamacros.h"
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
  enum Page { MAIN, ADD };

protected:
  void keyPressEvent(QKeyEvent *event) override;

public:
  MainWindow(QWidget * = nullptr);
  ~MainWindow();

public slots:
  void changePage(int);

signals:
  void clear();
};

#endif
