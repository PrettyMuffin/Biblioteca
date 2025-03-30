#include "../header/Biblioteca.h"
#include "qcontainerfwd.h"
#include "qcoreapplication.h"
#include "qjsonvalue.h"
#include <QJsonArray>
#include <QJsonObject>

bool Biblioteca::Contains(ElementoBiblioteca *elemento) const {
  for (auto e : tutti_elementi) {
    if (*e == *elemento)
      return true;
  }
  return false;
}

Biblioteca::Biblioteca(const vector<ElementoBiblioteca *> &elementi) {
  for (auto elemento : elementi) {
    tutti_elementi.push_back(elemento->clone());
  }
}

bool Biblioteca::add(ElementoBiblioteca *nuovo_elemento) {
  if (nuovo_elemento == nullptr)
    return false;
  if (Contains(nuovo_elemento))
    return false;
  tutti_elementi.push_back(nuovo_elemento);
  return true;
}

bool Biblioteca::remove(unsigned int index) {
  if (index >= tutti_elementi.size())
    return false;

  delete tutti_elementi[index];
  tutti_elementi.erase(tutti_elementi.begin() + index);
  return true;
}

bool Biblioteca::remove(ElementoBiblioteca *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  for (auto it = tutti_elementi.begin(); it != tutti_elementi.end(); ++it) {
    if (**it == *elemento) {
      delete *it;
      tutti_elementi.erase(it);
      return true;
    }
  }

  return false;
}

bool Biblioteca::update(unsigned int index, ElementoBiblioteca *elemento) {
  if (index >= tutti_elementi.size())
    return false;
  *tutti_elementi[index] = *elemento;
  return true;
}

bool Biblioteca::update(ElementoBiblioteca *old, ElementoBiblioteca *newel) {
  if (old == nullptr || newel == nullptr)
    return false;
  if (!Contains(old))
    return false;
  for (int i = 0; i < tutti_elementi.size(); ++i) {
    if (*tutti_elementi[i] == *old) {
      *tutti_elementi[i] = *newel;
      return true;
    }
  }
  return false;
}

QVector<ElementoBiblioteca *> Biblioteca::search(const QString &query) const {
  // se la query è vuota restituisce tutti gli elementi
  if (query.isEmpty()) {
    return tutti_elementi;
  }

  QVector<ElementoBiblioteca *> result;
  // costruzione della regex
  // nella ricerca in input da usare "," come separatore
  QStringList queryList = query.split(",");
  QString regex_str = "^";
  for (int i = 0; i < queryList.size(); i++) {
    if (queryList[i].contains(":")) {
      QStringList subqueryList = queryList[i].split((":"));
      regex_str += "^(?=.*" + subqueryList[0] + ":";
      regex_str += "[^\\\\]*" + subqueryList[1] + "[^\\\\]*(\\\\|$))";
    } else
      regex_str += "(?=.*" + queryList[i].trimmed() + ")";
  }
  regex_str += ".+$";
  QRegularExpression regex(regex_str,
                           QRegularExpression::CaseInsensitiveOption);
  // ricerca gli elementi che soddisfano la regex
  for (auto elementi : tutti_elementi) {
    if (regex.match(elementi->toString()).hasMatch())
      result.push_back(elementi);
  }
  return result;
}

QVector<ElementoBiblioteca *> Biblioteca::getElements() const {
  return tutti_elementi;
}

QJsonArray Biblioteca::toJson() const {
  QJsonArray array;
  for (auto elemento : tutti_elementi) {
    array.append(elemento->toJson());
  }
  return array;
}

void Biblioteca::clear() { tutti_elementi.clear(); }
