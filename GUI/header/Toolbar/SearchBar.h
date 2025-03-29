#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include "../Body/ContentView.h"
#include "qboxlayout.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

class SearchBar : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *layout;
  QLineEdit *searchInput;
  QPushButton *searchButton; // Boh non so se farlo rimanere, vedremo
  QPushButton *infoButton;
  void initInfoButton();

protected:
  void keyPressEvent(QKeyEvent *event) override;

public:
  SearchBar(QWidget * = nullptr);
  ~SearchBar();

private slots:
  void onInfoButtonClicked();

signals:
  void search(ContentView::FilterType, const QString &);
};

#endif
