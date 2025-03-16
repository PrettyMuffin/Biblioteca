#include "../../header/Toolbar/ToolBar.h"
#include "../../header/MainWindow.h"
#include "qboxlayout.h"
#include "qobject.h"
#include "qwidget.h"

Toolbar::Toolbar(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout(this);
  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent);
  opzioni = new Options(this, mainWindow);
  ricerca = new SearchBar(this);
  layout->addWidget(ricerca);
  layout->addWidget(opzioni);
}

Toolbar::~Toolbar() {
  delete layout;
  delete ricerca;
  delete opzioni;
}
