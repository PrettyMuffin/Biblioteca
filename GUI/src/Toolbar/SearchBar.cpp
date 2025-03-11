#include "../../header/Toolbar/SearchBar.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Toolbar/SearchBar.h"
#include "qboxlayout.h"
#include "qlineedit.h"
#include "qnamespace.h"
#include "qpushbutton.h"
#include "qwidget.h"

SearchBar::SearchBar(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout;
  searchInput = new QLineEdit;
  searchButton = new QPushButton;
  layout->addWidget(searchInput);
  layout->addWidget(searchButton);
}

void SearchBar::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter) {
    // dopo nel body me lo ripiglio
    emit onSearchEvent(searchInput->text());
  }
}
