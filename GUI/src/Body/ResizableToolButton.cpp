#include "../../header/Body/ResizableToolButton.h"

ResizableToolButton::ResizableToolButton(const QString &iconPath,
                                         QWidget *parent)
    : QToolButton(parent), m_iconPath(iconPath) {
  updateIcon();
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ResizableToolButton::resizeEvent(QResizeEvent *event) {
  QToolButton::resizeEvent(event);
  updateIcon();
}

void ResizableToolButton::updateIcon() {
  QPixmap pixmap(m_iconPath);
  if (!pixmap.isNull()) {
    // Scala l'immagine mantenendo le proporzioni (Qt::KeepAspectRatio)
    QPixmap scaledPixmap = pixmap.scaled(this->size());
    setIcon(QIcon(scaledPixmap));
    // setIconSize(scaledPixmap.size());
  }
}
