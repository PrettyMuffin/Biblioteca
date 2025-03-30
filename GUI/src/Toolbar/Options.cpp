#include "../../header/Toolbar/Options.h"
#include "../../../Logica/header/AppContext.h"
#include "../../../Logica/header/JSONController.h"
#include "../../../Logica/header/JSONError.h"
#include "../../header/MainWindow.h"
#include "../../header/UIContext.h"
#include "qboxlayout.h"
#include "qfiledialog.h"
#include "qicon.h"
#include "qmessagebox.h"
#include "qobject.h"
#include "qpushbutton.h"

Options::Options(QWidget *parent, MainWindow *mainWindow) : QWidget(parent) {
  add = new QPushButton;
  save = new QPushButton;
  import = new QPushButton;
  layout = new QHBoxLayout(this);
  layout->addWidget(add);
  layout->addWidget(save);
  layout->addWidget(import);
  add->setIcon(QIcon(":/images/img/add.png"));
  import->setIcon(QIcon(":/images/img/open.png"));
  save->setIcon(QIcon(":/images/img/save.png"));
  connect(add, &QPushButton::pressed, this,
          [this]() { this->onAddClicked(1); });
  connect(save, &QPushButton::pressed, this, &Options::onSaveClicked);
  connect(import, &QPushButton::pressed, this, &Options::onImportClicked);
  connect(this, &Options::onAddClicked, mainWindow, &MainWindow::changePage);
}

void Options::onSaveClicked() {
  QString path = QFileDialog::getSaveFileName(this, "File Json", "", "*.json");
  if (path.isEmpty()) {
    QMessageBox *errorBox = new QMessageBox(this);
    errorBox->setText("File non selezionato");
    errorBox->exec();
    return;
  }
  try {
    if (!path.endsWith(".json"))
      path += ".json";
    JSONController::saveOnFile(*AppContext::getBiblioteca(), path);
  } catch (JSONError e) {
    QMessageBox *errorBox = new QMessageBox(this);
    errorBox->setText(e.getMessage());
    errorBox->exec();
  }
}

void Options::onImportClicked() {
  QString path = QFileDialog::getOpenFileName(this, "File Json", "", "*.json");
  AppContext::provide(path);
  if (path.isEmpty()) {
    QMessageBox *errorBox = new QMessageBox(this);
    errorBox->setText("File non selezionato");
    errorBox->exec();
    return;
  }
  try {
    JSONController::loadFromFile(*AppContext::getBiblioteca(), path);
    emit(UIContext::getMainView()->updateViewRequested());
  } catch (JSONError e) {
    QMessageBox *errorBox = new QMessageBox(this);
    errorBox->setText(e.getMessage());
    errorBox->exec();
  }
}

Options::~Options() {}
