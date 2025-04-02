#ifndef LIBRO_H
#define LIBRO_H

#include "ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include <vector>

class Libro : public ElementoBiblioteca {
private:
  QString editore;
  QString ISBN;

public:
  struct JSON_FIELDS {
    static QString Editore;
    static QString ISBN;
  };
  Libro() = default;
  Libro(const QString &, const QString &, const QString &, const QString &,
        const QString &, const QVector<QString> &, const unsigned short int &,
        const QString &);
  Libro *clone() const override;
  QString getId() const override;
  QJsonObject toJson() const override;
  void fromJson(const QJsonObject &) override;
  void accept(ElementoBibliotecaVisitor *) override;
  QString toString() const override;

  QString getEditore() const;
  QString getISBN() const;

  virtual Libro &operator=(const Libro &other);
};

#endif
