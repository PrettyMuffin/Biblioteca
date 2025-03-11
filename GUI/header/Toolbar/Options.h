#ifndef OPTIONS_H
#define OPTIONS_H

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

public slots:
  void onAddClicked();
  void onSaveClicked();
  void onImportClicked();
};

#endif
