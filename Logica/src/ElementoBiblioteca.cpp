#include "../header/ElementoBiblioteca.h"
#include "qcoreapplication.h"
#include "qglobal.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
#include <QJsonArray>

ElementoBiblioteca::ElementoBiblioteca(
    const QString &titolo, const QString &genere, const QString &desc,
    const QVector<QString> &autori, const int &uscita, const QString &immagine)
    : titolo(titolo), genere(genere), descrizione(desc), autori(autori),
      uscita(uscita), immagine(immagine) {
  id = QString(this->titolo)
           .removeIf([](QChar c) { return c.isSpace(); })
           .toLower() +
       QString(autori.join("")).removeIf([](QChar c) { return c.isSpace(); });
}

QString ElementoBiblioteca::JSON_FIELDS::Titolo = "titolo";
QString ElementoBiblioteca::JSON_FIELDS::Genere = "genere";
QString ElementoBiblioteca::JSON_FIELDS::Descrizione = "descrizione";
QString ElementoBiblioteca::JSON_FIELDS::Autori = "autori";
QString ElementoBiblioteca::JSON_FIELDS::Uscita = "uscita";
QString ElementoBiblioteca::JSON_FIELDS::Tipo = "tipo";
QString ElementoBiblioteca::JSON_FIELDS::Immagine = "img";
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
  el[JSON_FIELDS::Autori] = jsonAuthorArray;
  el[JSON_FIELDS::Immagine] = immagine;
  return el;
}

void ElementoBiblioteca::registerObserver(ElementoBibliotecaObserver *obs) {
  observers.push_back(obs);
}

void ElementoBiblioteca::unregisterObserver(ElementoBibliotecaObserver *obs) {
  bool found = false;
  for (auto it = observers.begin(); it != observers.end() && !found; ++it) {
    if (*it == obs) {
      observers.erase(it);
      found = true;
    }
  }
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
  immagine = json[JSON_FIELDS::Immagine].toString();
  QJsonArray jsonAuthorArray = json[JSON_FIELDS::Autori].toArray();
  for (auto autore : jsonAuthorArray) {
    autori.push_back(autore.toString());
  }
  id = QString(titolo).removeIf([](QChar c) { return c.isSpace(); }).toLower();
}

QString ElementoBiblioteca::toString() const {
  QString res;
  res += "titolo:" + QString(titolo).removeIf([](QChar c) {
    return c.isSpace();
  }) + ESCAPE_CHAR;
  res += "genere:" + QString(genere).removeIf([](QChar c) {
    return c.isSpace();
  }) + ESCAPE_CHAR;
  res += "uscita:" + QString(QString::number(uscita)).removeIf([](QChar c) {
    return c.isSpace();
  }) + ESCAPE_CHAR;
  for (auto autore : autori) {
    res += "autore:" + QString(autore).removeIf([](QChar c) {
      return c.isSpace();
    }) + ESCAPE_CHAR;
  }
  return res.toLower();
}

QString ElementoBiblioteca::getTitolo() const { return titolo; }
QString ElementoBiblioteca::getGenere() const { return genere; }
QString ElementoBiblioteca::getDescrizione() const { return descrizione; }
const QVector<QString> ElementoBiblioteca::getAutori() const { return autori; }
QString ElementoBiblioteca::getImmagine() const { return immagine; }

int ElementoBiblioteca::getUscita() const { return uscita; }

ElementoBiblioteca &
ElementoBiblioteca::operator=(const ElementoBiblioteca &other) {
  if (this != &other) {
    titolo = other.titolo;
    genere = other.genere;
    descrizione = other.descrizione;
    uscita = other.uscita;
    autori = other.autori;
    id = other.id;
    immagine = other.immagine;
    for (auto observer : observers) {
      observer->notify(*this);
    }
  }
  return *this;
}
