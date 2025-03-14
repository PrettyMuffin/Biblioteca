#include "../header/ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
#include <QJsonArray>

ElementoBiblioteca::ElementoBiblioteca(const QString &titolo,
                                       const QString &genere,
                                       const QString &desc,
                                       const std::vector<QString> &autori,
                                       const int &uscita)
    : titolo(titolo), genere(genere), descrizione(desc), autori(autori),
      uscita(uscita) {
  // QString author_string("");
  // for (QString autore : autori) {
  //   author_string += autore.toLower();
  // }
  // id = this->titolo.toLower() + author_string;
  id = this->titolo.toLower();
}

QString ElementoBiblioteca::JSON_FIELDS::Titolo = "titolo";
QString ElementoBiblioteca::JSON_FIELDS::Genere = "genere";
QString ElementoBiblioteca::JSON_FIELDS::Descrizione = "descrizione";
QString ElementoBiblioteca::JSON_FIELDS::Autori = "autori";
QString ElementoBiblioteca::JSON_FIELDS::Uscita = "uscita";
QString ElementoBiblioteca::JSON_FIELDS::Tipo = "tipo";
QString ElementoBiblioteca::ESCAPE_CHAR = "\\";

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
  return lhs.getId() == rhs.getId();
}

void ElementoBiblioteca::fromJson(const QJsonObject &json) {
  titolo = json[JSON_FIELDS::Titolo].toString();
  genere = json[JSON_FIELDS::Genere].toString();
  descrizione = json[JSON_FIELDS::Descrizione].toString();
  uscita = json[JSON_FIELDS::Uscita].toInt();
  QJsonArray jsonAuthorArray = json[JSON_FIELDS::Autori].toArray();
  // QString author_string;
  for (auto autore : jsonAuthorArray) {
    autori.push_back(autore.toString());
    // author_string += autore.toString();
  }
  // id = this->titolo.toLower() + author_string;
  id = this->titolo.toLower();
}

QString ElementoBiblioteca::toString() const {
  QString res;
  res += titolo + ESCAPE_CHAR;
  res += genere + ESCAPE_CHAR;
  res += descrizione + ESCAPE_CHAR;
  res += QString::number(uscita) + ESCAPE_CHAR;
  for (int i = 0; i < autori.size() - 1; i++) {
    res += autori[i] + ESCAPE_CHAR;
  }
  res += autori[autori.size() - 1];
  return res;
}

QString ElementoBiblioteca::getTitolo() const { return titolo; }
QString ElementoBiblioteca::getGenere() const { return genere; }
QString ElementoBiblioteca::getDescrizione() const { return descrizione; }
const std::vector<QString> ElementoBiblioteca::getAutori() const {
  return autori;
}

int ElementoBiblioteca::getUscita() const { return uscita; }
