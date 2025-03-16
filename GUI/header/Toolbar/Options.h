#ifndef OPTIONS_H
#define OPTIONS_H

#include "qmenu.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class MainWindow;

class Options : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *layout;
  QPushButton *add;
  QPushButton *save;
  QPushButton *import;

public:
  Options(QWidget * = nullptr, MainWindow * = nullptr);
  ~Options();

signals:
  void onAddClicked(int);

public slots:
  void onSaveClicked();
  void onImportClicked();
};

#endif
