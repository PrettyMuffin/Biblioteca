#include "../header/MainWindow.h"
#include "../../Logica/header/AppContext.h"
#include "../../Logica/header/JSONController.h"
#include "qevent.h"
#include "qmessagebox.h"
#include "qnamespace.h"
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
  if (event->key() == Qt::Key_Escape && body->currentIndex() == Page::ADD) {
    emit(mainView->clear());
    body->setCurrentIndex(Page::MAIN);
  }
  if (event->keyCombination() == QKeyCombination(Qt::CTRL, Qt::Key_S)) {
    JSONController::saveOnFile(*AppContext::getBiblioteca(),
                               *AppContext::getFilePath());
    QMessageBox *conferma = new QMessageBox(this);
    conferma->setText("File salvato con successo");
    conferma->setStandardButtons(QMessageBox::Ok);
    conferma->exec();
  }
}
