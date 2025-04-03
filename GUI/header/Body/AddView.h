#ifndef ADDVIEW_H
#define ADDVIEW_H

#include "qhashfunctions.h"
#include "qlist.h"
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

  const QString DEFAULT_LIBRO_PATH;
  const QString DEFAULT_FILM_PATH;
  const QString DEFAULT_BRANO_PATH;
  QString path;

  void costruisciLibroPage(QWidget *libroPageWidget);
  void costruisciFilmPage(QWidget *filmPageWidget);
  void costruisciBranoPage(QWidget *branoPageWidget);

private slots:
  void onMainViewClear(QList<QWidget *>);

public:
  AddView(QWidget * = nullptr);
  static bool isValidInput(QList<QString>);
  ~AddView();

protected:
signals:
  void addLibro(const QString &titolo, const QString &genere,
                const QString &descrizione, const QString &editore,
                const QString &isbn, const QString &autore,
                const QString &annoPubblicazione, const QString &copertina);
  void addFilm(const QString &titolo, const QString &genere,
               const QString &descrizione, const QString &casa_cin,
               const QString &cast, const QString &annoPubblicazione,
               const QString &valutazione, const QString &copertina);
  void addBrano(const QString &titolo, const QString &genere,
                const QString &descrizione, const QString &album,
                const QString &durata, const QString &autore,
                const QString &annoPubblicazione, const QString &copertina);
  void CancelInsertion(int);

public slots:
  void onAddLibro(const QString &titolo, const QString &genere,
                  const QString &descrizione, const QString &editore,
                  const QString &isbn, const QString &autore,
                  const QString &annoPubblicazione, const QString &copertina);
  void onAddFilm(const QString &titolo, const QString &genere,
                 const QString &descrizione, const QString &casa_cin,
                 const QString &cast, const QString &annoPubblicazione,
                 const QString &valutazione, const QString &copertina);
  void onAddBrano(const QString &titolo, const QString &genere,
                  const QString &descrizione, const QString &album,
                  const QString &durata, const QString &autore,
                  const QString &annoPubblicazione, const QString &copertina);
};

#endif
