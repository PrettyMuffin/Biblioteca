#ifndef ADDVIEW_H
#define ADDVIEW_H

#include "qhashfunctions.h"
#include "qpushbutton.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QTabWidget>
#include <QWidget>
#include <initializer_list>

class AddView : public QWidget {
  Q_OBJECT

private:
  QTabWidget *layout;
  QWidget *libroPage;
  QWidget *filmPage;
  QWidget *branoPage;

  void costruisciLibroPage(QWidget *libroPageWidget);
  void costruisciFilmPage(QWidget *filmPageWidget);
  void costruisciBranoPage(QWidget *branoPageWidget);
  bool isValidInput(std::initializer_list<QString> input);

public:
  AddView(QWidget * = nullptr);
  ~AddView();

protected:
signals:
  void addLibro(const QString &titolo, const QString &genere,
                const QString &descrizione, const QString &editore,
                const QString &isbn, const QString &autore,
                const QString &annoPubblicazione);
  void addFilm(const QString &titolo, const QString &genere,
               const QString &descrizione, const QString &casa_cin,
               const QString &cast, const QString &annoPubblicazione,
               const QString &valutazione);
  void addBrano(const QString &titolo, const QString &genere,
                const QString &descrizione, const QString &album,
                const QString &durata, const QString &autore,
                const QString &annoPubblicazione);
  void CancelInsertion(int);

public slots:
  void onAddLibro(const QString &titolo, const QString &genere,
                  const QString &descrizione, const QString &editore,
                  const QString &isbn, const QString &autore,
                  const QString &annoPubblicazione);
  void onAddFilm(const QString &titolo, const QString &genere,
                 const QString &descrizione, const QString &casa_cin,
                 const QString &cast, const QString &annoPubblicazione,
                 const QString &valutazione);
  void onAddBrano(const QString &titolo, const QString &genere,
                  const QString &descrizione, const QString &album,
                  const QString &durata, const QString &autore,
                  const QString &annoPubblicazione);
};

#endif
