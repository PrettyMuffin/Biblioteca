#include "../../header/Body/AddView.h"
#include "../../../Logica/header/AppContext.h"
#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"
#include "../../header/MainWindow.h"
#include "../../header/UIContext.h"

#include "QApplication"
#include "qaction.h"
#include "qboxlayout.h"
#include "qcontainerfwd.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qevent.h"
#include "qfont.h"
#include "qglobal.h"
#include "qhashfunctions.h"
#include "qlabel.h"
#include "qlogging.h"
#include "qmenu.h"
#include "qmessagebox.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qspinbox.h"
#include "qtoolbutton.h"
#include "qwidget.h"
#include <QFileDialog>
#include <QToolButton>
#include <initializer_list>

AddView::AddView(QWidget *parent)
    : QWidget(parent), DEFAULT_LIBRO_PATH(":/images/img/libro.png"),
      DEFAULT_FILM_PATH(":/images/img/film.png"),
      DEFAULT_BRANO_PATH(":/images/img/brano.png") {
  layout = new QTabWidget(this);
  libroPage = new QWidget(this);
  filmPage = new QWidget(this);
  branoPage = new QWidget(this);

  costruisciLibroPage(libroPage);
  costruisciFilmPage(filmPage);
  costruisciBranoPage(branoPage);

  layout->addTab(libroPage, "Libro");
  layout->addTab(filmPage, "Film");
  layout->addTab(branoPage, "Brano");

  layout->setCurrentIndex(0); // tab del libro

  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent);
  if (mainWindow) {
    connect(this, &AddView::CancelInsertion, mainWindow,
            &MainWindow::changePage);
  }

  layout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(layout);
  setLayout(mainLayout);

  connect(this, &AddView::addLibro, this, &AddView::onAddLibro);
  connect(this, &AddView::addFilm, this, &AddView::onAddFilm);
  connect(this, &AddView::addBrano, this, &AddView::onAddBrano);
}

AddView::~AddView() {
  delete layout;
  delete libroPage;
  delete filmPage;
  delete branoPage;
}

void AddView::costruisciLibroPage(QWidget *libroPageWidget) {
  QHBoxLayout *layout = new QHBoxLayout(libroPageWidget);
  QToolButton *immagine = new QToolButton(libroPageWidget);
  path = DEFAULT_LIBRO_PATH;
  immagine->setStyleSheet("QToolButton { border-image: url(" + path +
                          ") 0 0 0 0 stretch stretch; }");

  immagine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *layoutInfo = new QVBoxLayout;

  QLabel *titolo_label = new QLabel("Titolo: ");
  QLineEdit *titolo_input = new QLineEdit;
  layoutInfo->addWidget(titolo_label);
  layoutInfo->addWidget(titolo_input);

  QLabel *genere_label = new QLabel("Genere: ");
  QPushButton *genere_input = new QPushButton;

  QMenu *genere_menu = new QMenu();
  genere_menu->addAction("Biografico");
  genere_menu->addAction("Azione");
  genere_menu->addAction("Horror");
  genere_menu->addAction("Umoristico");
  genere_menu->addAction("Giallo");
  genere_menu->addAction("Storico");
  genere_menu->addAction("Drammatico");
  genere_input->setMenu(genere_menu);
  genere_input->setText(genere_menu->actions()[0]->text());
  connect(genere_menu, &QMenu::aboutToShow, this,
          [genere_menu, genere_input]() {
            genere_menu->setMinimumWidth(genere_input->width());
          });
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this,
          [genere_input](QAction *action) {
            genere_input->setText(action->text());
          });

  layoutInfo->addWidget(genere_label);
  layoutInfo->addWidget(genere_input);

  QLabel *autore_label = new QLabel("Autore/i: ");
  QVBoxLayout *autore_layout = new QVBoxLayout;
  QLineEdit *autore_input = new QLineEdit;
  QLabel *precisazione =
      new QLabel("per molteplici autori separarli con una virgola!");
  QFont a = (precisazione->font());
  a.setPointSize(8);
  precisazione->setFont(a);
  autore_layout->addWidget(autore_input);
  autore_layout->addWidget(precisazione);

  layoutInfo->addWidget(autore_label);
  layoutInfo->addLayout(autore_layout);

  QLabel *editore_label = new QLabel("Editore: ");
  QLineEdit *editore_input = new QLineEdit;
  layoutInfo->addWidget(editore_label);
  layoutInfo->addWidget(editore_input);

  QLabel *uscita_label = new QLabel("Uscita (anno): ");
  QSpinBox *uscita_input = new QSpinBox;
  uscita_input->setMinimum(0);
  uscita_input->setMaximum(QDateTime::currentDateTime().date().year());
  layoutInfo->addWidget(uscita_label);
  layoutInfo->addWidget(uscita_input);

  QLabel *isbn_label = new QLabel("ISBN: ");
  QLineEdit *isbn_input = new QLineEdit;
  layoutInfo->addWidget(isbn_label);
  layoutInfo->addWidget(isbn_input);

  QLabel *descrizione_label = new QLabel("Descrizione: ");
  QLineEdit *descrizione_input = new QLineEdit;
  layoutInfo->addWidget(descrizione_label);
  layoutInfo->addWidget(descrizione_input);

  QHBoxLayout *bottoni_layout = new QHBoxLayout;
  QPushButton *annulla_button = new QPushButton("Annulla");
  QPushButton *conferma_button = new QPushButton("Conferma");
  bottoni_layout->addWidget(annulla_button);
  bottoni_layout->addWidget(conferma_button);
  layoutInfo->addLayout(bottoni_layout);
  connect(annulla_button, &QPushButton::clicked, this, [=]() {
    titolo_input->clear();
    genere_input->setText(genere_menu->actions()[0]->text());
    autore_input->clear();
    editore_input->clear();
    uscita_input->clear();
    isbn_input->clear();
    descrizione_input->clear();
    path = DEFAULT_LIBRO_PATH;
    emit CancelInsertion(0);
  });
  connect(conferma_button, &QPushButton::clicked, this, [=]() {
    emit addLibro(titolo_input->text(), genere_input->text(),
                  descrizione_input->text(), editore_input->text(),
                  isbn_input->text(), autore_input->text(),
                  uscita_input->text(), path);
  });
  connect(immagine, &QToolButton::clicked, this, [=]() {
    QString newPath = QFileDialog::getOpenFileName(
        this, "Seleziona immagine", "", "Immagini (*.png *.jpg *.jpeg)");
    if (newPath.isEmpty()) {
      QMessageBox::critical(this, "Errore", "Nessun file selezionato",
                            QMessageBox::Ok);
      return;
    }
    path = newPath;
    immagine->setStyleSheet("QToolButton { border-image: url(" + path +
                            ") 0 0 0 0 stretch stretch; }");
  });
  layout->addWidget(immagine);
  layout->addLayout(layoutInfo);
  libroPageWidget->setLayout(layout);
}

void AddView::costruisciFilmPage(QWidget *filmPageWidget) {
  QHBoxLayout *layout = new QHBoxLayout(filmPageWidget);
  QToolButton *immagine = new QToolButton(filmPageWidget);
  path = ":/images/img/film.png";
  immagine->setStyleSheet("QToolButton { border-image: url(" + path +
                          ") 0 0 0 0 stretch stretch; }");

  immagine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *layoutInfo = new QVBoxLayout;

  QLabel *titolo_label = new QLabel("Titolo: ");
  QLineEdit *titolo_input = new QLineEdit;
  layoutInfo->addWidget(titolo_label);
  layoutInfo->addWidget(titolo_input);

  QLabel *genere_label = new QLabel("Genere: ");
  QPushButton *genere_input = new QPushButton;

  QMenu *genere_menu = new QMenu();
  genere_menu->addAction("Biografico");
  genere_menu->addAction("Azione");
  genere_menu->addAction("Horror");
  genere_menu->addAction("Commedia");
  genere_menu->addAction("Crime");
  genere_menu->addAction("Fiction");
  genere_menu->addAction("Drammatico");
  genere_input->setMenu(genere_menu);
  genere_input->setText(genere_menu->actions()[0]->text());
  connect(genere_menu, &QMenu::aboutToShow, this,
          [genere_menu, genere_input]() {
            genere_menu->setMinimumWidth(genere_input->width());
          });
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this,
          [genere_input](QAction *action) {
            genere_input->setText(action->text());
          });

  layoutInfo->addWidget(genere_label);
  layoutInfo->addWidget(genere_input);

  QVBoxLayout *autore_layout = new QVBoxLayout;
  QLineEdit *autore_input = new QLineEdit;
  QLabel *autore_label = new QLabel("Cast: ");
  QLabel *precisazione =
      new QLabel("separare con una virgola i membri del cast");
  QFont a = (precisazione->font());
  a.setPointSize(8);
  precisazione->setFont(a);
  autore_layout->addWidget(autore_input);
  autore_layout->addWidget(precisazione);

  layoutInfo->addWidget(autore_label);
  layoutInfo->addLayout(autore_layout);

  QLabel *casa_cinematografica_label = new QLabel("Casa Cinematografica: ");
  QLineEdit *casa_cinematografica_input = new QLineEdit;
  layoutInfo->addWidget(casa_cinematografica_label);
  layoutInfo->addWidget(casa_cinematografica_input);

  QLabel *uscita_label = new QLabel("Uscita (anno): ");
  QSpinBox *uscita_input = new QSpinBox;
  uscita_input->setMinimum(0);
  uscita_input->setMaximum(QDateTime::currentDateTime().date().year());
  layoutInfo->addWidget(uscita_label);
  layoutInfo->addWidget(uscita_input);

  QLabel *valutazione_label = new QLabel("Valutazione: ");
  QSpinBox *valutazione_input = new QSpinBox;
  valutazione_input->setMinimum(0);
  valutazione_input->setMaximum(10);
  layoutInfo->addWidget(valutazione_label);
  layoutInfo->addWidget(valutazione_input);

  QLabel *descrizione_label = new QLabel("Descrizione: ");
  QLineEdit *descrizione_input = new QLineEdit;
  layoutInfo->addWidget(descrizione_label);
  layoutInfo->addWidget(descrizione_input);

  QHBoxLayout *bottoni_layout = new QHBoxLayout;
  QPushButton *annulla_button = new QPushButton("Annulla");
  QPushButton *conferma_button = new QPushButton("Conferma");
  bottoni_layout->addWidget(annulla_button);
  bottoni_layout->addWidget(conferma_button);
  layoutInfo->addLayout(bottoni_layout);
  connect(annulla_button, &QPushButton::clicked, this, [=]() {
    titolo_input->clear();
    genere_input->setText(genere_menu->actions()[0]->text());
    autore_input->clear();
    valutazione_input->clear();
    uscita_input->clear();
    casa_cinematografica_input->clear();
    descrizione_input->clear();
    path = DEFAULT_FILM_PATH;
    emit CancelInsertion(0);
  });
  connect(conferma_button, &QPushButton::clicked, this, [=]() {
    emit addFilm(titolo_input->text(), genere_input->text(),
                 descrizione_input->text(), casa_cinematografica_input->text(),
                 autore_input->text(), uscita_input->text(),
                 valutazione_input->text(), path);
  });

  connect(immagine, &QToolButton::clicked, this, [=]() {
    QString newPath = QFileDialog::getOpenFileName(
        this, "Seleziona immagine", "", "Immagini (*.png *.jpg *.jpeg)");
    if (newPath.isEmpty()) {
      QMessageBox::critical(this, "Errore", "Nessun file selezionato",
                            QMessageBox::Ok);
      return;
    }
    path = newPath;
    immagine->setStyleSheet("QToolButton { border-image: url(" + path +
                            ") 0 0 0 0 stretch stretch; }");
  });
  layout->addWidget(immagine);
  layout->addLayout(layoutInfo);
  filmPageWidget->setLayout(layout);
}

void AddView::costruisciBranoPage(QWidget *branoPageWidget) {

  QHBoxLayout *layout = new QHBoxLayout(branoPageWidget);
  QToolButton *immagine = new QToolButton(branoPageWidget);
  path = ":/images/img/brano.png";
  immagine->setStyleSheet("QToolButton { border-image: url(" + path +
                          ") 0 0 0 0 stretch stretch; }");

  immagine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *layoutInfo = new QVBoxLayout;

  QLabel *titolo_label = new QLabel("Titolo: ");
  QLineEdit *titolo_input = new QLineEdit;
  layoutInfo->addWidget(titolo_label);
  layoutInfo->addWidget(titolo_input);

  QLabel *genere_label = new QLabel("Genere: ");
  QPushButton *genere_input = new QPushButton;

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
  genere_input->setMenu(genere_menu);
  genere_input->setText(genere_menu->actions()[0]->text());
  connect(genere_menu, &QMenu::aboutToShow, this,
          [genere_menu, genere_input]() {
            genere_menu->setMinimumWidth(genere_input->width());
          });
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this,
          [genere_input](QAction *action) {
            genere_input->setText(action->text());
          });

  layoutInfo->addWidget(genere_label);
  layoutInfo->addWidget(genere_input);

  QLabel *autore_label = new QLabel("Artista/i: ");
  QVBoxLayout *autore_layout = new QVBoxLayout;
  QLineEdit *autore_input = new QLineEdit;
  QLabel *precisazione =
      new QLabel("per più artisti separarli con una virgola!");
  QFont a = (precisazione->font());
  a.setPointSize(8);
  precisazione->setFont(a);
  autore_layout->addWidget(autore_input);
  autore_layout->addWidget(precisazione);

  layoutInfo->addWidget(autore_label);
  layoutInfo->addLayout(autore_layout);

  QLabel *album_label = new QLabel("Album: ");
  QLineEdit *album_input = new QLineEdit;
  layoutInfo->addWidget(album_label);
  layoutInfo->addWidget(album_input);

  QLabel *durata_label = new QLabel("Durata: ");
  QHBoxLayout *durata_layout = new QHBoxLayout;
  QLabel *minuti_label = new QLabel("Minuti: ");
  QSpinBox *minuti_input = new QSpinBox;
  minuti_input->setMinimum(0);
  minuti_input->setMaximum(59);
  QLabel *secondi_label = new QLabel("Secondi: ");
  QSpinBox *secondi_input = new QSpinBox;
  secondi_input->setMinimum(0);
  secondi_input->setMaximum(59);
  durata_layout->addWidget(minuti_label);
  durata_layout->addWidget(minuti_input);
  durata_layout->addWidget(secondi_label);
  durata_layout->addWidget(secondi_input);
  layoutInfo->addWidget(durata_label);
  layoutInfo->addLayout(durata_layout);

  QLabel *uscita_label = new QLabel("Uscita (anno): ");
  QSpinBox *uscita_input = new QSpinBox;
  uscita_input->setMaximum(QDateTime::currentDateTime().date().year());
  layoutInfo->addWidget(uscita_label);
  layoutInfo->addWidget(uscita_input);

  QLabel *descrizione_label = new QLabel("Descrizione: ");
  QLineEdit *descrizione_input = new QLineEdit;
  layoutInfo->addWidget(descrizione_label);
  layoutInfo->addWidget(descrizione_input);

  QHBoxLayout *bottoni_layout = new QHBoxLayout;
  QPushButton *annulla_button = new QPushButton("Annulla");
  QPushButton *conferma_button = new QPushButton("Conferma");
  bottoni_layout->addWidget(annulla_button);
  bottoni_layout->addWidget(conferma_button);
  layoutInfo->addLayout(bottoni_layout);

  connect(annulla_button, &QPushButton::clicked, this, [=]() {
    titolo_input->clear();
    genere_input->setText(genere_menu->actions()[0]->text());
    autore_input->clear();
    minuti_input->clear();
    secondi_input->clear();
    uscita_input->clear();
    album_input->clear();
    descrizione_input->clear();
    path = DEFAULT_BRANO_PATH;

    emit CancelInsertion(0);
  });
  connect(conferma_button, &QPushButton::clicked, this, [=]() {
    QString durata_secondi = QString::number(minuti_input->text().toInt() * 60 +
                                             secondi_input->text().toInt());
    emit addBrano(titolo_input->text(), genere_input->text(),
                  descrizione_input->text(), album_input->text(),
                  durata_secondi, autore_input->text(), uscita_input->text(),
                  path);
  });

  connect(immagine, &QToolButton::clicked, this, [=]() {
    QString newPath = QFileDialog::getOpenFileName(
        this, "Seleziona immagine", "", "Immagini (*.png *.jpg *.jpeg)");
    if (newPath.isEmpty()) {
      QMessageBox::critical(this, "Errore", "Nessun file selezionato",
                            QMessageBox::Ok);
      return;
    }
    path = newPath;
    immagine->setStyleSheet("QToolButton { border-image: url(" + path +
                            ") 0 0 0 0 stretch stretch; }");
  });

  layout->addWidget(immagine);
  layout->addLayout(layoutInfo);
  branoPageWidget->setLayout(layout);
}

void AddView::onAddLibro(const QString &titolo, const QString &genere,
                         const QString &descrizione, const QString &editore,
                         const QString &isbn, const QString &autore,
                         const QString &annoPubblicazione,
                         const QString &copertina) {
  if (!isValidInput({titolo, genere, descrizione, editore, isbn, autore,
                     annoPubblicazione}))
    return;

  Libro *libro = new Libro(titolo, genere, descrizione, editore, isbn,
                           autore.split(",").toVector(),
                           annoPubblicazione.toInt(), copertina);
  AppContext::getBiblioteca()->add(libro);
}

void AddView::onAddFilm(const QString &titolo, const QString &genere,
                        const QString &descrizione, const QString &casa_cin,
                        const QString &cast, const QString &annoPubblicazione,
                        const QString &valutazione, const QString &copertina) {
  qDebug() << "controllo film";
  if (!isValidInput({titolo, genere, descrizione, casa_cin, cast,
                     annoPubblicazione, valutazione}))
    return;
  qDebug() << "film in aggiunta";
  Film *film = new Film(titolo, genere, descrizione, casa_cin,
                        cast.split(",").toVector(), annoPubblicazione.toInt(),
                        valutazione.toInt(), copertina);
  AppContext::getBiblioteca()->add(film);
  qDebug() << "film aggiunto";
}

void AddView::onAddBrano(const QString &titolo, const QString &genere,
                         const QString &descrizione, const QString &album,
                         const QString &durata, const QString &autore,
                         const QString &annoPubblicazione,
                         const QString &copertina) {
  if (!isValidInput({titolo, genere, descrizione, album, durata, autore,
                     annoPubblicazione}))
    return;

  Brano *brano = new Brano(titolo, genere, descrizione, album, durata.toInt(),
                           autore.split(",").toVector(),
                           annoPubblicazione.toInt(), copertina);

  AppContext::getBiblioteca()->add(brano);
}

void AddView::onMainViewClear(QList<QWidget *> widgets) {
  for (auto widget : widgets) {
    if (auto spinBox = qobject_cast<QSpinBox *>(widget)) {
      spinBox->clear();
    } else if (auto lineEdit = qobject_cast<QLineEdit *>(widget)) {
      lineEdit->clear();
    } else if (auto comboBox = qobject_cast<QTextEdit *>(widget)) {
      comboBox->clear();
    }
  }
}

bool AddView::isValidInput(QList<QString> input) {
  QString error_string = "";
  bool isValid = true;
  for (auto cit = input.begin(); cit != input.end() && isValid; ++cit) {
    QString str = *cit;
    if (str.isEmpty()) {
      error_string = "Campi vuoti";
      isValid = false;
    } else if (str.contains("\\") || str.contains(":")) {
      error_string = "Carattere non valido, l'input non può contenere \\ o :";
      isValid = false;
    }
  }
  if (!isValid) {
    QMessageBox *error = new QMessageBox(QMessageBox::Critical, "Errore",
                                         error_string, QMessageBox::Ok);
    error->exec();
  }
  return isValid;
}
