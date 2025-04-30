#ifndef RESIZABLE_TOOL_BUTTON_H
#define RESIZABLE_TOOL_BUTTON_H

#include <QPixmap>
#include <QResizeEvent>
#include <QToolButton>

class ResizableToolButton : public QToolButton {
  Q_OBJECT
public:
  ResizableToolButton(const QString &, QWidget * = nullptr);

protected:
  void resizeEvent(QResizeEvent *event) override;

private:
  QString m_iconPath;
  QSize m_baseSize;

  void updateIcon();
};
#endif
