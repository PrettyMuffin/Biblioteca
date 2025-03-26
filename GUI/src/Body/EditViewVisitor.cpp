#include "../../header/Body/EditViewVisitor.h"

#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qobjectdefs.h"
#include "qspinbox.h"
#include "qtextedit.h"
#include "qwidget.h"
#include <QPushButton>
#include <QTextEdit>

EditViewVisitor::EditViewVisitor() {}
EditViewVisitor::~EditViewVisitor() { delete widget; }

QWidget *EditViewVisitor::getWidget() { return widget; }

void EditViewVisitor::visit(Libro *libro) {
  widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel;

  QHBoxLayout *titolo_layout = new QHBoxLayout();
  QLabel *titlolo_label = new QLabel("Titolo: ", widget);
  QLineEdit *titolo_edit = new QLineEdit(libro->getTitolo(), widget);
  titolo_layout->addWidget(titlolo_label);
  titolo_layout->addWidget(titolo_edit);

  QHBoxLayout *autore_layout = new QHBoxLayout();

  QLabel *autore_label = new QLabel("Autore/i: ", widget);
  QLineEdit *autore_edit = new QLineEdit(libro->getAutori().join(", "), widget);
  autore_layout->addWidget(autore_label);
  autore_layout->addWidget(autore_edit);

  QHBoxLayout *genere_layout = new QHBoxLayout();
  QLabel *genere_label = new QLabel("Genere: ", widget);
  QLineEdit *genere_edit = new QLineEdit(libro->getGenere(), widget);
  genere_layout->addWidget(genere_label);
  genere_layout->addWidget(genere_edit);

  QHBoxLayout *isbn_layout = new QHBoxLayout();
  QLabel *isbn_label = new QLabel("ISBN: ", widget);
  QLineEdit *isbn_edit = new QLineEdit(libro->getISBN(), widget);
  isbn_layout->addWidget(isbn_label);
  isbn_layout->addWidget(isbn_edit);

  QHBoxLayout *editore_layout = new QHBoxLayout();
  QLabel *editore_label = new QLabel("Editore: ", widget);
  QLineEdit *editore_edit = new QLineEdit(libro->getEditore(), widget);
  editore_layout->addWidget(editore_label);
  editore_layout->addWidget(editore_edit);

  QHBoxLayout *uscita_layout = new QHBoxLayout();
  QLabel *uscita = new QLabel("Anno di uscita: ", widget);
  QSpinBox *uscita_edit = new QSpinBox(widget);
  uscita_edit->setValue(libro->getUscita());
  uscita_edit->setMinimum(0);
  uscita_edit->setMaximum(2023);
  uscita_layout->addWidget(uscita);
  uscita_layout->addWidget(uscita_edit);

  QVBoxLayout *descrizione_layout = new QVBoxLayout();
  QLabel *decrizione_label = new QLabel("Descrizione: ", widget);
  QTextEdit *descrizione_edit = new QTextEdit(libro->getDescrizione(), widget);
  descrizione_layout->addWidget(decrizione_label);
  descrizione_layout->addWidget(descrizione_edit);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addLayout(titolo_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(genere_layout);
  layout->addLayout(isbn_layout);
  layout->addLayout(editore_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(descrizione_layout);

  widget->setLayout(layout);
}

void EditViewVisitor::visit(Brano *brano) {
  widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel;

  QHBoxLayout *titolo_layout = new QHBoxLayout();
  QLabel *titoloLabel = new QLabel("Titolo: ", widget);
  QLineEdit *titolo_edit = new QLineEdit(brano->getTitolo(), widget);
  titolo_layout->addWidget(titoloLabel);
  titolo_layout->addWidget(titolo_edit);

  QHBoxLayout *autore_layout = new QHBoxLayout();
  QLabel *autoreLabel = new QLabel("Autore/i: ", widget);
  QLineEdit *autore_edit = new QLineEdit(brano->getAutori().join(", "), widget);
  autore_layout->addWidget(autoreLabel);
  autore_layout->addWidget(autore_edit);

  QHBoxLayout *album_layout = new QHBoxLayout();
  QLabel *albumLabel = new QLabel("Album: ", widget);
  QLineEdit *album_edit = new QLineEdit(brano->getAlbum(), widget);
  album_layout->addWidget(albumLabel);
  album_layout->addWidget(album_edit);

  QHBoxLayout *genere_layout = new QHBoxLayout();
  QLabel *genereLabel = new QLabel("Genere: ", widget);
  QLineEdit *genere_edit = new QLineEdit(brano->getGenere(), widget);
  genere_layout->addWidget(genereLabel);
  genere_layout->addWidget(genere_edit);

  QVBoxLayout *durata_layout = new QVBoxLayout();
  QLabel *durataLabel = new QLabel("Durata: ", widget);
  QHBoxLayout *minuti_layout = new QHBoxLayout();
  QLabel *minutiLabel = new QLabel("Minuti: ", widget);
  QSpinBox *minuti_edit = new QSpinBox();
  minuti_edit->setValue(brano->getDurata() / 60);
  QLabel *secondiLabel = new QLabel("Secondi: ", widget);
  QSpinBox *secondi_edit = new QSpinBox();
  secondi_edit->setValue(brano->getDurata() % 60);
  minuti_layout->addWidget(minutiLabel);
  minuti_layout->addWidget(minuti_edit);
  minuti_layout->addWidget(secondiLabel);
  minuti_layout->addWidget(secondi_edit);
  durata_layout->addWidget(durataLabel);
  durata_layout->addLayout(minuti_layout);

  QHBoxLayout *uscita_layout = new QHBoxLayout();
  QLabel *uscita = new QLabel("Anno di uscita: ", widget);
  QSpinBox *uscita_edit = new QSpinBox();
  uscita_edit->setValue(brano->getUscita());
  uscita_layout->addWidget(uscita);
  uscita_layout->addWidget(uscita_edit);

  QVBoxLayout *descrizione_layout = new QVBoxLayout();
  QLabel *descrizione = new QLabel("Descrizione: ", widget);
  QTextEdit *descrizione_edit = new QTextEdit(brano->getDescrizione(), widget);
  descrizione_layout->addWidget(descrizione);
  descrizione_layout->addWidget(descrizione_edit);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addLayout(titolo_layout);
  layout->addLayout(durata_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(album_layout);
  layout->addLayout(genere_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(descrizione_layout);

  widget->setLayout(layout);
}

void EditViewVisitor::visit(Film *film) {
  widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QLabel *pixmap = new QLabel;
  QHBoxLayout *titolo_layout = new QHBoxLayout();
  QLabel *titlolo = new QLabel("Titolo: ", widget);
  QLineEdit *titolo_edit = new QLineEdit(film->getTitolo(), widget);
  titolo_layout->addWidget(titlolo);
  titolo_layout->addWidget(titolo_edit);

  QHBoxLayout *autore_layout = new QHBoxLayout();
  QLabel *autoreLabel = new QLabel("Autore/i: ", widget);
  QLineEdit *autore_edit = new QLineEdit(film->getAutori().join(", "), widget);
  autore_layout->addWidget(autoreLabel);
  autore_layout->addWidget(autore_edit);

  QHBoxLayout *genere_layout = new QHBoxLayout();
  QLabel *genereLabel = new QLabel("Genere: ", widget);
  QLineEdit *genere_edit = new QLineEdit(film->getGenere(), widget);
  genere_layout->addWidget(genereLabel);
  genere_layout->addWidget(genere_edit);

  QHBoxLayout *valutazione_layout = new QHBoxLayout();
  QLabel *valutazione = new QLabel("Valutazione (0-10): ", widget);
  QSpinBox *valutazione_spinbox = new QSpinBox(widget);
  valutazione_spinbox->setMinimum(0);
  valutazione_spinbox->setMaximum(10);
  valutazione_spinbox->setValue(film->getValutazione());
  valutazione_layout->addWidget(valutazione);
  valutazione_layout->addWidget(valutazione_spinbox);

  QHBoxLayout *casa_layout = new QHBoxLayout();
  QLabel *casa = new QLabel("Casa cinematografica: ", widget);
  QLineEdit *casa_edit = new QLineEdit(film->getCasaCinematografica(), widget);
  casa_layout->addWidget(casa);
  casa_layout->addWidget(casa_edit);

  QHBoxLayout *uscita_layout = new QHBoxLayout();
  QLabel *uscita = new QLabel("Anno di uscita: ", widget);
  QLineEdit *uscita_edit =
      new QLineEdit(QString::number(film->getUscita()), widget);
  uscita_layout->addWidget(uscita);
  uscita_layout->addWidget(uscita_edit);

  QVBoxLayout *descrizione_layout = new QVBoxLayout();
  QLabel *descrizione = new QLabel("Descrizione: ", widget);
  QTextEdit *descrizione_edit = new QTextEdit(film->getDescrizione(), widget);
  descrizione_layout->addWidget(descrizione);
  descrizione_layout->addWidget(descrizione_edit);

  QHBoxLayout *pulsanti_layout = new QHBoxLayout();
  QPushButton *salva = new QPushButton("Salva", widget);
  QPushButton *annulla = new QPushButton("Annulla", widget);
  pulsanti_layout->addWidget(annulla);
  pulsanti_layout->addWidget(salva);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addLayout(titolo_layout);
  layout->addLayout(genere_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(casa_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(valutazione_layout);
  layout->addLayout(descrizione_layout);
  layout->addLayout(pulsanti_layout);

  widget->setLayout(layout);
}
