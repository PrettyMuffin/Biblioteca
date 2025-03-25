#ifndef GUI_CONTEXT_H
#define GUI_CONTEXT_H

#include "Body/MainView.h"
#include "qlayout.h"

class UIContext {
private:
  static MainView *mainView;

public:
  static void setMainView(MainView *window);
  static void clearLayout(QLayout *layout);
  static MainView *getMainView();
};

#endif
