#include "../../header/Body/DetailViewVisitor.h"
#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"

#include "qboxlayout.h"
#include "qlabel.h"

DetailViewVisitor::DetailViewVisitor() {
  widget = new QWidget();
  layout = new QVBoxLayout(widget);
  initPulsanti();

  connect(_chiudi, &QPushButton::clicked, this, &DetailViewVisitor::chiudi);
  connect(_elimina, &QPushButton::clicked, this, &DetailViewVisitor::elimina);
  connect(_modifica, &QPushButton::clicked, this, &DetailViewVisitor::modifica);
}

DetailViewVisitor::~DetailViewVisitor() { delete widget; }

QWidget *DetailViewVisitor::getWidget() const { return widget; }

void DetailViewVisitor::initPulsanti() {
  pulsanti_layout = new QHBoxLayout();
  _chiudi = new QPushButton("Chiudi", widget);
  _elimina = new QPushButton("Elimina", widget);
  _modifica = new QPushButton("Modifica", widget);
  pulsanti_layout->addWidget(_chiudi);
  pulsanti_layout->addWidget(_elimina);
  pulsanti_layout->addWidget(_modifica);
}

void DetailViewVisitor::visit(Libro *libro) {
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel(widget);
  pixmap->setPixmap(QPixmap(libro->getImmagine()));
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
  layout->addLayout(pulsanti_layout);
}

void DetailViewVisitor::visit(Brano *brano) {
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel(widget);
  pixmap->setPixmap(QPixmap(brano->getImmagine()));
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
  layout->addLayout(pulsanti_layout);
}

void DetailViewVisitor::visit(Film *film) {
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel(widget);
  pixmap->setPixmap(QPixmap(film->getImmagine()));
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
  layout->addLayout(pulsanti_layout);
}
