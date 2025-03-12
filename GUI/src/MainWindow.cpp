#include "../header/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  toolbar = new Toolbar(this);
  body = new QStackedWidget(this);
  mainView = new MainView(this);
  addView = new AddView(this);

  layout->addWidget(toolbar);
  layout->addWidget(body);
  body->addWidget(mainView);
  body->addWidget(addView);
}
