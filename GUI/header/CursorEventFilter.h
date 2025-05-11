#ifndef CURSOR_EVENT_FILTER
#define CURSOR_EVENT_FILTER

#include "qobject.h"

class CursorEventFilter : public QObject {
protected:
  bool eventFilter(QObject *, QEvent *) override;

public:
  explicit CursorEventFilter(QObject * = nullptr);
};

#endif
