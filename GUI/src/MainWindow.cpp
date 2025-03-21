#include "../header/MainWindow.h"
#include "qwidget.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout(this);
  // qua ordine di inizalizzazione importante dato che nella search bar si usa
  // il mainView
  body = new QStackedWidget(this);
  mainView = new MainView(this);
  addView = new AddView(this);
  toolbar = new Toolbar(this);

  body->addWidget(mainView);
  body->addWidget(addView);

  layout->addWidget(toolbar);
  layout->addWidget(body);

  setLayout(layout);
}

void MainWindow::changePage(int page) { body->setCurrentIndex(page); }

MainWindow::~MainWindow() {
  delete layout;
  delete toolbar;
  delete body;
  delete mainView;
  delete addView;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape && body->currentIndex() == 1) {
    body->setCurrentIndex(0);
  }
}
