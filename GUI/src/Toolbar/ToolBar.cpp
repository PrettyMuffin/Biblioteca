#include "../../header/Toolbar/ToolBar.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qwidget.h"

Toolbar::Toolbar(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout;
  logo = new QLabel;
  layout->addWidget(logo);
  layout->addWidget(&ricerca);
  layout->addWidget(&opzioni);
}
