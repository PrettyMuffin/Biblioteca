#ifndef GUI_CONTEXT_H
#define GUI_CONTEXT_H

#include "Body/MainView.h"

// SINGLETON

class UIContext {
private:
  static MainView *mainView;

public:
  static void setMainView(MainView *window);
  static MainView *getMainView();
};

#endif
