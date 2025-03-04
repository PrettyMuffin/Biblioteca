#ifndef ELEMENTOBIBIBLIOTECA_H
#define ELEMENTOBIBIBLIOTECA_H

#include "../header/ElementoBibliotecaObserver.h"
#include "../header/ElementoBibliotecaVisitor.h"
#include "Persona.h"
#include "qcoreapplication.h"
#include "qdeadlinetimer.h"
#include "qset.h"
#include <vector>

class ElementoBiblioteca {
  friend bool operator==(const ElementoBiblioteca &,
                         const ElementoBiblioteca &);

protected:
  QString id; // titolo(to lower) + autore(to lower)
private:
  QString titolo;
  QString genere;
  QString descrizione;
  std::vector<QString> autori;
  unsigned short int uscita; // anno pubblicazione
  std::vector<ElementoBibliotecaObserver *> observers;

public:
  class JSON_FIELDS {
  public:
    static QString Titolo;
    static QString Genere;
    static QString Descrizione;
    static QString Autori;
    static QString Uscita;
    static QString Tipo;
  };
  ElementoBiblioteca() = default;
  ElementoBiblioteca(const QString &, const QString &, const QString &,
                     const std::vector<QString> &, const unsigned short int &);
  virtual QJsonObject toJson() const;
  virtual void fromJson(const QJsonObject &);
  virtual void accept(ElementoBiblotecaVisitor *) = 0;
  virtual ElementoBiblioteca *clone() const = 0;
  void registerObserver(ElementoBibliotecaObserver *);
  virtual ~ElementoBiblioteca();
};

bool operator==(const ElementoBiblioteca &lhs, const ElementoBiblioteca &rhs);

#endif
