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
  QVector<QString> autori;
  int uscita; // anno pubblicazione
  QString immagine;
  QVector<ElementoBibliotecaObserver *> observers;

public:
  struct JSON_FIELDS {
    static QString Titolo;
    static QString Genere;
    static QString Descrizione;
    static QString Autori;
    static QString Uscita;
    static QString Tipo;
    static QString Immagine;
  };
  ElementoBiblioteca() = default;
  ElementoBiblioteca(const QString &, const QString &, const QString &,
                     const QVector<QString> &, const int &, const QString &);
  virtual ElementoBiblioteca *clone() const = 0;
  ElementoBiblioteca(const ElementoBiblioteca &) = default;
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
  QString getImmagine() const;
  const QVector<QString> getAutori() const;

  ElementoBiblioteca &operator=(const ElementoBiblioteca &other);
};

bool operator==(const ElementoBiblioteca &lhs, const ElementoBiblioteca &rhs);

#endif
