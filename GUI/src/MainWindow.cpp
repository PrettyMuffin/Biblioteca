#include "../header/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  toolbar = new Toolbar(this);
  body = new QStackedWidget(this);
  mainView = new MainView(this);
  addView = new AddView(this);
  body->addWidget(mainView);
  body->addWidget(addView);

  layout->addWidget(toolbar);
  layout->addWidget(body);
}

MainWindow::~MainWindow() {
  delete layout;
  delete toolbar;
  delete body;
  delete mainView;
  delete addView;
}
