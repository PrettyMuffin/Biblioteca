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
protected:
  QString id;
  static QString ESCAPE_CHAR;

private:
  QString titolo;
  QString genere;
  QString descrizione;
  std::vector<QString> autori;
  int uscita; // anno pubblicazione
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
                     const std::vector<QString> &, const int &);
  virtual ElementoBiblioteca *clone() const = 0;
  virtual ~ElementoBiblioteca();

  virtual QJsonObject toJson() const;
  virtual void fromJson(const QJsonObject &);

  virtual void accept(ElementoBibliotecaVisitor *) = 0;
  virtual QString toString() const;
  void registerObserver(ElementoBibliotecaObserver *);
  void unregisterObserver(ElementoBibliotecaObserver *);

  virtual QString getId() const = 0;
  QString getTitolo() const;
  QString getGenere() const;
  QString getDescrizione() const;
  int getUscita() const;
  const std::vector<QString> getAutori() const;

  virtual ElementoBiblioteca &operator=(const ElementoBiblioteca &other);
};

bool operator==(const ElementoBiblioteca &lhs, const ElementoBiblioteca &rhs);

#endif
