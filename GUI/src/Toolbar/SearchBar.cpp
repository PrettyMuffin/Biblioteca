#include "../../header/Toolbar/SearchBar.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Toolbar/SearchBar.h"
#include "qboxlayout.h"
#include "qlineedit.h"
#include "qnamespace.h"
#include "qpushbutton.h"
#include "qwidget.h"

SearchBar::SearchBar(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout(this);
  searchInput = new QLineEdit(this);
  searchButton = new QPushButton(this);
  searchButton->setIcon(QIcon(":/images/img/search.png"));
  layout->addWidget(searchInput);
  layout->addWidget(searchButton);
}

void SearchBar::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    // dopo nel body me lo ripiglio
    emit onSearchEvent(searchInput->text());
  }
}

SearchBar::~SearchBar() {
  delete layout;
  delete searchInput;
  delete searchButton;
}
