#include "../../header/Toolbar/SearchBar.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Body/ContentView.h"
#include "../../header/Toolbar/SearchBar.h"
#include "../../header/UIContext.h"
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

  MainView *mainView = UIContext::getMainView();
  if (mainView) {
    connect(searchButton, &QPushButton::clicked, this,
            [this]() { emit search(ContentView::QUERY, searchInput->text()); });
    connect(this, &SearchBar::search, mainView, &MainView::searchRequested);
  }
}

void SearchBar::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    emit search(ContentView::QUERY, searchInput->text());
  }
}

SearchBar::~SearchBar() {
  delete layout;
  delete searchInput;
  delete searchButton;
}
