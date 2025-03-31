#include "../../header/Toolbar/SearchBar.h"
#include "../../../Logica/header/AppContext.h"
#include "../../header/Body/ContentView.h"
#include "../../header/Toolbar/SearchBar.h"
#include "../../header/UIContext.h"
#include "qboxlayout.h"
#include "qlineedit.h"
#include "qmessagebox.h"
#include "qnamespace.h"
#include "qpushbutton.h"
#include "qwidget.h"

SearchBar::SearchBar(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout(this);
  searchInput = new QLineEdit(this);
  searchButton = new QPushButton(this);
  searchButton->setIcon(QIcon(":/images/img/search.png"));
  searchInput->setStyleSheet(
      "background-color: #e3eafc; padding: .3em 0.1em; color: #1e2122");

  initInfoButton();
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

void SearchBar::initInfoButton() {
  infoButton = new QPushButton(this);
  infoButton->setIcon(QIcon(":/images/img/info.png"));
  layout->addWidget(infoButton);
  connect(infoButton, &QPushButton::clicked, this,
          &SearchBar::onInfoButtonClicked);
}

void SearchBar::onInfoButtonClicked() {
  QMessageBox *messageBox = new QMessageBox(this);
  messageBox->setWindowTitle("Come usare la barra di ricerca");
  messageBox->setText(
      "Per cercare un elemento basta digitare nella barra di ricerca ciò che "
      "si sta cercando.\nPer essere il più precisi possibile: specificare "
      "il campo e la ricerca.\nEs.'autore: Orwell'.\nPer cercare un elemento "
      "con più caratteristiche è sufficiente separare i filtri con una "
      "virgola. \nEs. 'autore: Orwell, titolo: 1984' oppure 'Orwell, titolo: "
      "1984', non è strettamente necessario specificare il campo in caso di "
      "ricerca su più caratteristiche.");
  messageBox->exec();
}
