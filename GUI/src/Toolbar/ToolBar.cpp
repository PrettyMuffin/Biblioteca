#include "../../header/Toolbar/ToolBar.h"
#include "qboxlayout.h"
#include "qwidget.h"

Toolbar::Toolbar(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout;
  layout->addWidget(&ricerca);
  layout->addWidget(&opzioni);
}

Toolbar::~Toolbar() { delete layout; }
