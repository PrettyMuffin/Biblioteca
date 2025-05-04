#include "../../header/Body/EditViewVisitor.h"
#include "../../header/Body/AddView.h"

#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"
#include "qboxlayout.h"
#include "qcoreapplication.h"
#include "qdatetime.h"
#include "qicon.h"
#include "qlabel.h"
#include "qlayoutitem.h"
#include "qlineedit.h"
#include "qmessagebox.h"
#include "qnamespace.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qpixmap.h"
#include "qpushbutton.h"
#include "qspinbox.h"
#include "qtextedit.h"
#include "qwidget.h"
#include <QFileDialog>
#include <QPushButton>
#include <QTextEdit>
#include <qmenu.h>

EditViewVisitor::EditViewVisitor() {
  widget = new QWidget();
  layout = new QVBoxLayout(widget);
  initPulsanti();

  connect(_annulla, &QPushButton::clicked, this, &EditViewVisitor::annulla);
}
EditViewVisitor::~EditViewVisitor() { delete widget; }

void EditViewVisitor::initPulsanti() {
  pulsanti_layout = new QHBoxLayout();
  _modifica = new QPushButton("Modifica", widget);
  _annulla = new QPushButton("Annulla", widget);
  pulsanti_layout->addWidget(_annulla);
  pulsanti_layout->addWidget(_modifica);
}

QWidget *EditViewVisitor::getWidget() { return widget; }

void EditViewVisitor::visit(Libro *libro) {
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QPushButton *pixmap = new QPushButton(widget);
  pixmap->setIcon(QPixmap(libro->getImmagine()));
  pixmap->setIconSize(QSize(180, 280));
  pixmap->setFlat(true);
  pixmap->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  newPath = libro->getImmagine();

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
  QPushButton *genere_edit = new QPushButton(libro->getGenere(), widget);
  genere_layout->addWidget(genere_label);
  QMenu *genere_menu = new QMenu();
  genere_menu->addAction("Biografico");
  genere_menu->addAction("Azione");
  genere_menu->addAction("Fantascienza");
  genere_menu->addAction("Horror");
  genere_menu->addAction("Umoristico");
  genere_menu->addAction("Giallo");
  genere_menu->addAction("Storico");
  genere_menu->addAction("Drammatico");
  genere_edit->setMenu(genere_menu);
  connect(genere_menu, &QMenu::aboutToShow, this, [genere_menu, genere_edit]() {
    genere_menu->setMinimumWidth(genere_edit->width());
  });
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this, [genere_edit](QAction *action) {
    genere_edit->setText(action->text());
  });
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
  uscita_edit->setMaximum(QDate::currentDate().year());
  uscita_layout->addWidget(uscita);
  uscita_layout->addWidget(uscita_edit);

  QVBoxLayout *descrizione_layout = new QVBoxLayout();
  QLabel *decrizione_label = new QLabel("Descrizione: ", widget);
  QTextEdit *descrizione_edit = new QTextEdit(libro->getDescrizione(), widget);
  descrizione_layout->addWidget(decrizione_label);
  descrizione_layout->addWidget(descrizione_edit);

  connect(_modifica, &QPushButton::clicked, this, [=]() {
    QList<QString> input = {
        titolo_edit->text(),
        genere_edit->text(),
        descrizione_edit->toPlainText(),
        editore_edit->text(),
        isbn_edit->text(),
        autore_edit->text(),
        uscita_edit->text(),
    };
    if (!AddView::isValidInput(input))
      return;
    Libro *nLibro = new Libro(input[0], input[1], input[2], input[3], input[4],
                              input[5].split(","), input[6].toInt(), newPath);
    emit modifica(nLibro);
  });

  connect(pixmap, &QPushButton::clicked, this, [=]() {
    QString path = QFileDialog::getOpenFileName(
        this, "Open Image", "", "Image Files (*.png *.jpg *.jpeg)");
    if (path.isEmpty()) {
      QMessageBox::critical(this, "Error", "Nessuna Immagine selezionata");
      return;
    }
    newPath = path;
    pixmap->setIcon(QPixmap(newPath));
  });

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->setAlignment(pixmap, Qt::AlignHCenter);
  layout->addLayout(titolo_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(genere_layout);
  layout->addLayout(isbn_layout);
  layout->addLayout(editore_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(descrizione_layout);
  layout->addLayout(pulsanti_layout);
}

void EditViewVisitor::visit(Brano *brano) {
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QPushButton *pixmap = new QPushButton(widget);
  pixmap->setIcon(QPixmap(brano->getImmagine()));
  pixmap->setIconSize(QSize(180, 280));
  pixmap->setFlat(true);
  pixmap->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  newPath = brano->getImmagine();

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
  QPushButton *genere_edit = new QPushButton(brano->getGenere(), widget);
  QMenu *genere_menu = new QMenu();
  genere_menu->addAction("Pop");
  genere_menu->addAction("Rock");
  genere_menu->addAction("Metal");
  genere_menu->addAction("R&B");
  genere_menu->addAction("Rap");
  genere_menu->addAction("Dance");
  genere_menu->addAction("Blues");
  genere_menu->addAction("Classica");
  genere_menu->addAction("Jazz");
  genere_menu->addAction("Colonne Sonore");
  genere_edit->setMenu(genere_menu);
  connect(genere_menu, &QMenu::aboutToShow, this, [genere_menu, genere_edit]() {
    genere_menu->setMinimumWidth(genere_edit->width());
  });
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this, [genere_edit](QAction *action) {
    genere_edit->setText(action->text());
  });
  genere_layout->addWidget(genereLabel);
  genere_layout->addWidget(genere_edit);

  QVBoxLayout *durata_layout = new QVBoxLayout();
  QLabel *durataLabel = new QLabel("Durata: ", widget);
  QHBoxLayout *minuti_layout = new QHBoxLayout();
  QLabel *minutiLabel = new QLabel("Minuti: ", widget);
  QSpinBox *minuti_edit = new QSpinBox();
  minuti_edit->setValue(brano->getDurata() / 60);
  minuti_edit->setMinimum(0);
  minuti_edit->setMaximum(59);
  QLabel *secondiLabel = new QLabel("Secondi: ", widget);
  QSpinBox *secondi_edit = new QSpinBox();
  secondi_edit->setMinimum(0);
  secondi_edit->setMaximum(59);
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
  uscita_edit->setMinimum(0);
  uscita_edit->setMaximum(QDate::currentDate().year());
  uscita_edit->setValue(brano->getUscita());
  uscita_layout->addWidget(uscita);
  uscita_layout->addWidget(uscita_edit);

  QVBoxLayout *descrizione_layout = new QVBoxLayout();
  QLabel *descrizione = new QLabel("Descrizione: ", widget);
  QTextEdit *descrizione_edit = new QTextEdit(brano->getDescrizione(), widget);
  descrizione_layout->addWidget(descrizione);
  descrizione_layout->addWidget(descrizione_edit);

  connect(_modifica, &QPushButton::clicked, this, [=]() {
    QString durata =
        QString::number(minuti_edit->value() * 60 + secondi_edit->value());
    QList<QString> input = {
        titolo_edit->text(),
        genere_edit->text(),
        descrizione_edit->toPlainText(),
        album_edit->text(),
        durata,
        autore_edit->text(),
        uscita_edit->text(),
    };
    if (!AddView::isValidInput(input))
      return;
    Brano *brano =
        new Brano(input[0], input[1], input[2], input[3], input[4].toInt(),
                  input[5].split(","), input[6].toInt(), newPath);
    emit modifica(brano);
  });

  connect(pixmap, &QPushButton::clicked, this, [=]() {
    QString path = QFileDialog::getOpenFileName(
        this, "Open Image", "", "Image Files (*.png *.jpg *.jpeg)");
    if (path.isEmpty()) {
      QMessageBox::critical(this, "Error", "Nessuna Immagine selezionata");
      return;
    }
    newPath = path;
    pixmap->setIcon(QPixmap(newPath));
  });

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->setAlignment(pixmap, Qt::AlignHCenter);
  layout->addLayout(titolo_layout);
  layout->addLayout(durata_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(album_layout);
  layout->addLayout(genere_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(descrizione_layout);
  layout->addLayout(pulsanti_layout);
}

void EditViewVisitor::visit(Film *film) {
  QLabel *info = new QLabel("Info sull'elemento", widget);
  QPushButton *pixmap = new QPushButton(widget);
  pixmap->setIcon(QPixmap(film->getImmagine()));
  pixmap->setIconSize(QSize(180, 280));
  pixmap->setFlat(true);
  pixmap->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  newPath = film->getImmagine();

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
  QPushButton *genere_edit = new QPushButton(film->getGenere(), widget);
  QMenu *genere_menu = new QMenu();
  genere_menu->addAction("Biografico");
  genere_menu->addAction("Azione");
  genere_menu->addAction("Horror");
  genere_menu->addAction("Commedia");
  genere_menu->addAction("Crime");
  genere_menu->addAction("Fiction");
  genere_menu->addAction("Drammatico");
  genere_edit->setMenu(genere_menu);
  connect(genere_menu, &QMenu::aboutToShow, this, [genere_menu, genere_edit]() {
    genere_menu->setMinimumWidth(genere_edit->width());
  });
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this, [genere_edit](QAction *action) {
    genere_edit->setText(action->text());
  });
  genere_layout->addWidget(genereLabel);
  genere_layout->addWidget(genere_edit);

  QHBoxLayout *valutazione_layout = new QHBoxLayout();
  QLabel *valutazione = new QLabel("Valutazione (0-10): ", widget);
  QSpinBox *valutazione_edit = new QSpinBox(widget);
  valutazione_edit->setMinimum(0);
  valutazione_edit->setMaximum(10);
  valutazione_edit->setValue(film->getValutazione());
  valutazione_layout->addWidget(valutazione);
  valutazione_layout->addWidget(valutazione_edit);

  QHBoxLayout *casa_layout = new QHBoxLayout();
  QLabel *casa = new QLabel("Casa cinematografica: ", widget);
  QLineEdit *casa_edit = new QLineEdit(film->getCasaCinematografica(), widget);
  casa_layout->addWidget(casa);
  casa_layout->addWidget(casa_edit);

  QHBoxLayout *uscita_layout = new QHBoxLayout();
  QLabel *uscita = new QLabel("Anno di uscita: ", widget);
  QSpinBox *uscita_edit = new QSpinBox(widget);
  uscita_edit->setValue(film->getUscita());
  uscita_edit->setMinimum(0);
  uscita_edit->setMaximum(QDate::currentDate().year());
  uscita_layout->addWidget(uscita);
  uscita_layout->addWidget(uscita_edit);

  QVBoxLayout *descrizione_layout = new QVBoxLayout();
  QLabel *descrizione = new QLabel("Descrizione: ", widget);
  QTextEdit *descrizione_edit = new QTextEdit(film->getDescrizione(), widget);
  descrizione_layout->addWidget(descrizione);
  descrizione_layout->addWidget(descrizione_edit);

  connect(_modifica, &QPushButton::clicked, this, [=]() {
    QList<QString> input = {
        titolo_edit->text(),
        genere_edit->text(),
        descrizione_edit->toPlainText(),
        casa_edit->text(),
        autore_edit->text(),
        uscita_edit->text(),
        valutazione_edit->text(),
    };
    if (!AddView::isValidInput(input))
      return;

    Film *film =
        new Film(input[0], input[1], input[2], input[3], input[4].split(","),
                 input[5].toInt(), input[6].toInt(), newPath);
    emit modifica(film);
  });

  connect(pixmap, &QPushButton::clicked, this, [=]() {
    QString path = QFileDialog::getOpenFileName(
        this, "Open Image", "", "Image Files (*.png *.jpg *.jpeg)");
    if (path.isEmpty()) {
      QMessageBox::critical(this, "Error", "Nessuna Immagine selezionata");
      return;
    }
    newPath = path;
    pixmap->setIcon(QPixmap(newPath));
  });

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->setAlignment(pixmap, Qt::AlignHCenter);
  layout->addLayout(titolo_layout);
  layout->addLayout(genere_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(casa_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(valutazione_layout);
  layout->addLayout(descrizione_layout);
  layout->addLayout(pulsanti_layout);
}
