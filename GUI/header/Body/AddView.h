#ifndef ADDVIEW_H
#define ADDVIEW_H

#include "qpushbutton.h"
#include "qtmetamacros.h"
#include "qwidget.h"
#include <QTabWidget>
#include <QWidget>

class AddView : public QWidget {
  Q_OBJECT

private:
  enum Pagina { LIBRO, FILM, BRANO };
  QTabWidget *layout;
  QWidget *libroPage;
  QWidget *filmPage;
  QWidget *branoPage;
  void costruisciLibroPage(QWidget *libroPageWidget);
  void costruisciFilmPage(QWidget *filmPageWidget);
  void costruisciBranoPage(QWidget *branoPageWidget);

public:
  AddView(QWidget *parent = nullptr);
  ~AddView();

signals:
  // TODO: tengo solo per idea, da riordinare ordine dei parametri
  //  void libroAdded(const QString &titolo, const std::vector<QString> &autore,
  //                  const QString &editore, const QString &isbn,
  //                  const QString &genere, const QString &annoPubblicazione,
  //                  const QString &numeroPagine);
  //  void filmAdded(const QString &titolo, const std::vector<QString> &regista,
  //                 const QString &durata, const QString &genere,
  //                 const QString &annoPubblicazione);
  //  void branoAdded(const QString &titolo, const std::vector<QString> &autore,
  //                  const QString &durata, const QString &genere,
  //                  const QString &annoPubblicazione);
  void addLibro();
  void addFilm();
  void addBrano();
  void CancelInsertion(int);

public slots:
  void onAddLibro();
  void onAddFilm();
  void onAddBrano();
};

#endif
