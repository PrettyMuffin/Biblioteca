#ifndef ELEMENTO_BIBLIOTECA_OBSERVER_H
#define ELEMENTO_BIBLIOTECA_OBSERVER_H

class ElementoBiblioteca;

class ElementoBibliotecaObserver {
public:
  virtual void notify(ElementoBiblioteca &) = 0;
  virtual ~ElementoBibliotecaObserver() = default;
};

#endif
