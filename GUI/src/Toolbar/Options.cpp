#include "../../header/Toolbar/Options.h"
#include "../../../Logica/header/AppContext.h"
#include "../../../Logica/header/JSONController.h"
#include "qboxlayout.h"
#include "qpushbutton.h"

Options::Options(QWidget *parent) : QWidget(parent) {
  add = new QPushButton;
  save = new QPushButton;
  import = new QPushButton;
  layout = new QHBoxLayout(this);
  layout->addWidget(add);
  layout->addWidget(save);
  layout->addWidget(import);

  connect(add, &QPushButton::pressed, this, &Options::onAddClicked);
  connect(save, &QPushButton::pressed, this, &Options::onSaveClicked);
  connect(import, &QPushButton::pressed, this, &Options::onImportClicked);
}

void Options::onAddClicked() {}

void Options::onSaveClicked() {
  QString path;
  // mostro file dialog
  JSONController jsonController;
  jsonController.saveOnFile(*AppContext::getBiblioteca(), path); // per ora
}

void Options::onImportClicked() {}
