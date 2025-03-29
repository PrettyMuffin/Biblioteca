#ifndef ELEMENTO_BIBLIOTECA_VISITOR_H
#define ELEMENTO_BIBLIOTECA_VISITOR_H

class Libro;
class Brano;
class Film;

class ElementoBibliotecaVisitor {
public:
  virtual void visit(Libro *) = 0;
  virtual void visit(Brano *) = 0;
  virtual void visit(Film *) = 0;
  virtual ~ElementoBibliotecaVisitor() = default; // per evitare warning
};

#endif
