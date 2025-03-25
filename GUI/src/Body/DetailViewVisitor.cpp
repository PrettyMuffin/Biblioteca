#include "../../header/Body/DetailViewVisitor.h"
#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"

#include "qboxlayout.h"
#include "qlabel.h"

DetailViewVisitor::DetailViewVisitor() {}

DetailViewVisitor::~DetailViewVisitor() { delete widget; }

QWidget *DetailViewVisitor::getWidget() const { return widget; }

void DetailViewVisitor::visit(Libro *libro) {
  widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel;
  QLabel *titlolo = new QLabel("Titolo: " + libro->getTitolo(), widget);
  const QVector<QString> autori = libro->getAutori();
  QLabel *autore =
      new QLabel("Autore/i: " + libro->getAutori().join(", "), widget);
  QLabel *genere = new QLabel("Genere: " + libro->getGenere(), widget);
  QLabel *isbn = new QLabel("ISBN: " + libro->getISBN(), widget);
  QLabel *editore = new QLabel("Editore: " + libro->getEditore(), widget);
  QLabel *uscita = new QLabel(
      "Anno di uscita: " + QString::number(libro->getUscita()), widget);
  QLabel *descrizione =
      new QLabel("Descrizione: " + libro->getDescrizione(), widget);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addWidget(titlolo);
  layout->addWidget(autore);
  layout->addWidget(genere);
  layout->addWidget(isbn);
  layout->addWidget(editore);
  layout->addWidget(uscita);
  layout->addWidget(descrizione);

  widget->setLayout(layout);
}

void DetailViewVisitor::visit(Brano *brano) {
  widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel;
  QLabel *titlolo = new QLabel("Titolo: " + brano->getTitolo(), widget);
  QLabel *autoreLabel =
      new QLabel("Autore/i: " + brano->getAutori().join(", "), widget);
  QLabel *album = new QLabel("Album: " + brano->getAlbum(), widget);
  QLabel *genere = new QLabel("Genere: " + brano->getGenere(), widget);
  QLabel *durata =
      new QLabel("Durata: " + QString::number(brano->getDurata()), widget);
  QLabel *uscita = new QLabel(
      "Anno di uscita: " + QString::number(brano->getUscita()), widget);
  QLabel *descrizione =
      new QLabel("Descrizione: " + brano->getDescrizione(), widget);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addWidget(titlolo);
  layout->addWidget(durata);
  layout->addWidget(autoreLabel);
  layout->addWidget(album);
  layout->addWidget(genere);
  layout->addWidget(uscita);
  layout->addWidget(descrizione);

  widget->setLayout(layout);
}

void DetailViewVisitor::visit(Film *film) {
  widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel;
  QLabel *titlolo = new QLabel("Titolo: " + film->getTitolo(), widget);
  QLabel *autoreLabel =
      new QLabel("Cast: " + film->getAutori().join(", "), widget);
  QLabel *valutazione = new QLabel(
      "Valutazione: " + QString::number(film->getValutazione()) + "/10",
      widget);
  QLabel *genere = new QLabel("Genere: " + film->getGenere(), widget);
  QLabel *casa = new QLabel(
      "Casa cinematografica: " + film->getCasaCinematografica(), widget);
  QLabel *uscita = new QLabel(
      "Anno di uscita: " + QString::number(film->getUscita()), widget);
  QLabel *descrizione =
      new QLabel("Descrizione: " + film->getDescrizione(), widget);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addWidget(titlolo);
  layout->addWidget(autoreLabel);
  layout->addWidget(genere);
  layout->addWidget(casa);
  layout->addWidget(uscita);
  layout->addWidget(valutazione);
  layout->addWidget(descrizione);

  widget->setLayout(layout);
}
