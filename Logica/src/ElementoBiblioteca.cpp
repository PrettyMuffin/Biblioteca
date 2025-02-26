#include "../header/ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
#include <QJsonArray>

ElementoBiblioteca::ElementoBiblioteca(const QString &titolo,
                                       const QString &genere,
                                       const QString &desc,
                                       const std::vector<QString> &autori,
                                       const unsigned short int &uscita)
    : titolo(titolo), genere(genere), descrizione(desc), autori(autori),
      uscita(uscita) {
  QString author_string("");
  for (QString autore : autori) {
    author_string += autore.toLower();
  }
  id = this->titolo.toLower() + author_string;
}

QString ElementoBiblioteca::JSON_FIELDS::Titolo = "titolo";
QString ElementoBiblioteca::JSON_FIELDS::Genere = "genere";
QString ElementoBiblioteca::JSON_FIELDS::Descrizione = "descrizione";
QString ElementoBiblioteca::JSON_FIELDS::Autori = "autori";
QString ElementoBiblioteca::JSON_FIELDS::Uscita = "uscita";

QJsonObject ElementoBiblioteca::toJson() const {
  QJsonObject el;
  el[JSON_FIELDS::Titolo] = titolo;
  el[JSON_FIELDS::Genere] = genere;
  el[JSON_FIELDS::Descrizione] = descrizione;
  el[JSON_FIELDS::Uscita] = uscita;
  QJsonArray jsonAuthorArray;
  for (auto autore : autori) {
    jsonAuthorArray.append(QJsonValue(autore));
  }
  el[JSON_FIELDS::Titolo] = jsonAuthorArray;
  return el;
}

void ElementoBiblioteca::registerObserver(ElementoBibliotecaObserver *obs) {
  observers.push_back(obs);
}

ElementoBiblioteca::~ElementoBiblioteca() {
  for (auto observer : observers) {
    delete observer;
  }
}

bool operator==(const ElementoBiblioteca &lhs, const ElementoBiblioteca &rhs) {
  return lhs.id == rhs.id;
}
