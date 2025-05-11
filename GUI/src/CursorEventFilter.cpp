#include "../header/CursorEventFilter.h"
#include "qcoreevent.h"
#include "qobject.h"
#include "qsharedpointer.h"
#include "qwidget.h"
#include <QCursor>
#include <QEvent>
#include <QObject>
#include <QWidget>

CursorEventFilter::CursorEventFilter(QObject *parent) : QObject(parent) {}

bool CursorEventFilter::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() != QEvent::Enter && event->type() != QEvent::Leave)
    return false;

  if (event->type() == QEvent::Enter) {
    if (auto widget = qobject_cast<QWidget *>(obj))
      widget->setCursor(Qt::PointingHandCursor);

  } else if (event->type() == QEvent::Leave) {
    if (auto widget = qobject_cast<QWidget *>(obj))
      widget->unsetCursor();
  }
  return QObject::eventFilter(obj, event);
}
