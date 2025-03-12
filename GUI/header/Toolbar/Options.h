#ifndef OPTIONS_H
#define OPTIONS_H

#include "qtmetamacros.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class Options : public QWidget {
  Q_OBJECT
private:
  QHBoxLayout *layout;
  QPushButton *add;
  QPushButton *save;
  QPushButton *import;

public:
  Options(QWidget * = nullptr);
  ~Options();

signals:
  void onAddClicked();

public slots:
  void onSaveClicked();
  void onImportClicked();
};

#endif
