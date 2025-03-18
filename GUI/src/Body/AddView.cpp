#include "../../header/Body/AddView.h"
#include "../../header/MainWindow.h"
#include "qaction.h"
#include "qboxlayout.h"
#include "qlabel.h"

#include "qmenu.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qspinbox.h"
#include "qwidget.h"

AddView::AddView(QWidget *parent) : QWidget(parent) {
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

  layout->setCurrentIndex(Pagina::LIBRO);

  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent);
  if (mainWindow) {
    connect(this, &AddView::CancelInsertion, mainWindow,
            &MainWindow::changePage);
  }

  layout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(layout);
  setLayout(mainLayout);
}

AddView::~AddView() {
  delete layout;
  delete libroPage;
  delete filmPage;
  delete branoPage;
}

void AddView::costruisciLibroPage(QWidget *libroPageWidget) {
  QHBoxLayout *layout = new QHBoxLayout(libroPageWidget);
  QLabel *immagine = new QLabel;

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
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this,
          [genere_input](QAction *action) {
            genere_input->setText(action->text());
          });

  layoutInfo->addWidget(genere_label);
  layoutInfo->addWidget(genere_input);

  QLabel *autore_label = new QLabel("Autore/i: ");
  QHBoxLayout *autore_layout = new QHBoxLayout;
  QLineEdit *autore_input = new QLineEdit;
  QLabel *precisazione =
      new QLabel("per molteplici autori separarli con una virgola!");
  autore_layout->addWidget(autore_input);
  autore_layout->addWidget(precisazione);

  layoutInfo->addWidget(autore_label);
  layoutInfo->addLayout(autore_layout);

  QLabel *editore_label = new QLabel("Editore: ");
  QLineEdit *editore_input = new QLineEdit;
  layoutInfo->addWidget(editore_label);
  layoutInfo->addWidget(editore_input);

  QLabel *uscita_label = new QLabel("Uscita (anno): ");
  QLineEdit *uscita_input = new QLineEdit;
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
  QObject::connect(annulla_button, &QPushButton::clicked, this,
                   [this]() { emit this->CancelInsertion(0); });
  QObject::connect(conferma_button, &QPushButton::clicked, this,
                   [this]() { emit this->addLibro(); });
  layout->addWidget(immagine);
  layout->addLayout(layoutInfo);
  libroPageWidget->setLayout(layout);
}

void AddView::costruisciFilmPage(QWidget *filmPageWidget) {
  QHBoxLayout *layout = new QHBoxLayout(filmPageWidget);
  QLabel *immagine = new QLabel;

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
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this,
          [genere_input](QAction *action) {
            genere_input->setText(action->text());
          });

  layoutInfo->addWidget(genere_label);
  layoutInfo->addWidget(genere_input);

  QHBoxLayout *autore_layout = new QHBoxLayout;
  QLineEdit *autore_input = new QLineEdit;
  QLabel *autore_label = new QLabel("Cast: ");
  QLabel *precisazione =
      new QLabel("separare con una virgola i membri del cast");
  autore_layout->addWidget(autore_input);
  autore_layout->addWidget(precisazione);

  layoutInfo->addWidget(autore_label);
  layoutInfo->addLayout(autore_layout);

  QLabel *casa_cinematografica_label = new QLabel("Casa Cinematografica: ");
  QLineEdit *casa_cinematografica_input = new QLineEdit;
  layoutInfo->addWidget(casa_cinematografica_label);
  layoutInfo->addWidget(casa_cinematografica_input);

  QLabel *uscita_label = new QLabel("Uscita (anno): ");
  QLineEdit *uscita_input = new QLineEdit;
  layoutInfo->addWidget(uscita_label);
  layoutInfo->addWidget(uscita_input);

  QLabel *valutazione_label = new QLabel("Valutazione: ");
  QLineEdit *valutazione_input = new QLineEdit;
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
  connect(annulla_button, &QPushButton::clicked, this,
          [this]() { emit this->CancelInsertion(0); });
  connect(conferma_button, &QPushButton::clicked, this,
          [this]() { emit this->addFilm(); });

  layout->addWidget(immagine);
  layout->addLayout(layoutInfo);
  filmPageWidget->setLayout(layout);
}

void AddView::costruisciBranoPage(QWidget *branoPageWidget) {

  QHBoxLayout *layout = new QHBoxLayout(branoPageWidget);
  QLabel *immagine = new QLabel();

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
  // modifico input di bottone
  connect(genere_menu, &QMenu::triggered, this,
          [genere_input](QAction *action) {
            genere_input->setText(action->text());
          });

  layoutInfo->addWidget(genere_label);
  layoutInfo->addWidget(genere_input);

  QLabel *autore_label = new QLabel("Artista/i: ");
  QHBoxLayout *autore_layout = new QHBoxLayout;
  QLineEdit *autore_input = new QLineEdit;
  QLabel *precisazione =
      new QLabel("per più artisti separarli con una virgola!");
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
  QLabel *secondi_label = new QLabel("Secondi: ");
  QSpinBox *secondi_input = new QSpinBox;
  durata_layout->addWidget(minuti_label);
  durata_layout->addWidget(minuti_input);
  durata_layout->addWidget(secondi_label);
  durata_layout->addWidget(secondi_input);
  layoutInfo->addWidget(durata_label);
  layoutInfo->addLayout(durata_layout);

  QLabel *uscita_label = new QLabel("Uscita (anno): ");
  QLineEdit *uscita_input = new QLineEdit;
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
  connect(annulla_button, &QPushButton::clicked, this,
          [this]() { emit this->CancelInsertion(0); });
  connect(conferma_button, &QPushButton::clicked, this,
          [this]() { emit this->addBrano(); });

  layout->addWidget(immagine);
  layout->addLayout(layoutInfo);
  branoPageWidget->setLayout(layout);
}

void AddView::onAddLibro() {}
void AddView::onAddFilm() {}
void AddView::onAddBrano() {}
