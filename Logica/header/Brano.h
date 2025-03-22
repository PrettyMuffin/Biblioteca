#ifndef BRANO_H
#define BRANO_H

#include "Biblioteca.h"
#include "ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include <vector>

class Brano : public ElementoBiblioteca {
private:
  QString album;
  unsigned int durata; // secondi
public:
  class JSON_FIELDS {
  public:
    static QString Album;
    static QString Durata;
  };
  Brano() = default;
  Brano(const QString &, const QString &, const QString &, const QString &,
        const unsigned int &, const std::vector<QString> &,
        const unsigned short int &);
  Brano *clone() const override;
  void fromJson(const QJsonObject &) override;
  void accept(ElementoBibliotecaVisitor *) override;
  QJsonObject toJson() const override;
  QString getId() const override;
  QString toString() const override;

  QString getAlbum() const;
  unsigned int getDurata() const;

  Brano &operator=(const Brano &other);
};

#endif
