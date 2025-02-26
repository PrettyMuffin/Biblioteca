#include "../header/Film.h"
#include "qcoreapplication.h"
#include "qjsonobject.h"

Film::Film(const QString &titolo, const QString &genere,
           const QString &descrizione, const QString &ca_cin,
           const std::vector<QString> &autori, const unsigned short int &uscita,
           const unsigned short int &valutazione)
    : ElementoBiblioteca(titolo, genere, descrizione, autori, uscita),
      casa_cinematografica(ca_cin), valutazione(valutazione) {}

QString Film::JSON_FIELDS::Titolo = ElementoBiblioteca::JSON_FIELDS::Titolo;
QString Film::JSON_FIELDS::Genere = ElementoBiblioteca::JSON_FIELDS::Genere;
QString Film::JSON_FIELDS::Descrizione =
    ElementoBiblioteca::JSON_FIELDS::Descrizione;
QString Film::JSON_FIELDS::Autori = ElementoBiblioteca::JSON_FIELDS::Autori;
QString Film::JSON_FIELDS::Uscita = ElementoBiblioteca::JSON_FIELDS::Uscita;
QString Film::JSON_FIELDS::Valutazione = "valutazione";
QString Film::JSON_FIELDS::Casa_Cinematografica = "casa";

QJsonObject Film::toJson() const {
  QJsonObject brano;
  QJsonObject parent = ElementoBiblioteca::toJson();

  brano[JSON_FIELDS::Titolo] = parent[JSON_FIELDS::Titolo];
  brano[JSON_FIELDS::Genere] = parent[JSON_FIELDS::Genere];
  brano[JSON_FIELDS::Descrizione] = parent[JSON_FIELDS::Descrizione];
  brano[JSON_FIELDS::Autori] = parent[JSON_FIELDS::Autori];
  brano[JSON_FIELDS::Uscita] = parent[JSON_FIELDS::Uscita];
  brano[JSON_FIELDS::Valutazione] = valutazione;
  brano[JSON_FIELDS::Casa_Cinematografica] = casa_cinematografica;
  return brano;
}
Film *Film::clone() const { return new Film(*this); }

void Film::accept(ElementoBiblotecaVisitor *visitor) { visitor->visit(this); }
