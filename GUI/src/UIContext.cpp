#include "../header/UIContext.h"

MainView *UIContext::getMainView() { return mainView; }

void UIContext::setMainView(MainView *view) { mainView = view; }

void UIContext::clearLayout(QLayout *layout) {
  if (!layout)
    return;

  while (QLayoutItem *item = layout->takeAt(0)) {
    if (QWidget *w = item->widget())
      w->deleteLater();
    else if (QLayout *l = item->layout())
      clearLayout(l);
    delete item;
  }
}

MainView *UIContext::mainView = nullptr;
