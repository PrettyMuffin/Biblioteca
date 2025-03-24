#include "../../header/Body/EditViewVisitor.h"

#include "../../../Logica/header/Brano.h"
#include "../../../Logica/header/Film.h"
#include "../../../Logica/header/Libro.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qspinbox.h"

EditViewVisitor::EditViewVisitor() {}
EditViewVisitor::~EditViewVisitor() {}

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
  const QVector<QString> autori = libro->getAutori();
  QString stringa_autori = autori.join(", ");
  // for (int i = 0; i < autori.size() - 1; i++) {
  //   stringa_autori += autori[i] + ", ";
  // }
  // stringa_autori += autori.back();
  QLabel *autore_label = new QLabel("Autore/i: ", widget);
  QLineEdit *autore_edit = new QLineEdit(stringa_autori, widget);
  autore_layout->addWidget(autore_label);
  autore_layout->addWidget(autore_edit);

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
  QLineEdit *descrizione_edit = new QLineEdit(libro->getDescrizione(), widget);
  descrizione_layout->addWidget(decrizione_label);
  descrizione_layout->addWidget(descrizione_edit);

  layout->addWidget(info);
  layout->addWidget(pixmap);
  layout->addLayout(titolo_layout);
  layout->addLayout(autore_layout);
  layout->addLayout(isbn_layout);
  layout->addLayout(editore_layout);
  layout->addLayout(uscita_layout);
  layout->addLayout(descrizione_layout);

  widget->setLayout(layout);
}

void EditViewVisitor::visit(Brano *brano) {}

void EditViewVisitor::visit(Film *film) {}
