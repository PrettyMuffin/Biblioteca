#include "../header/UIContext.h"

MainView *UIContext::getMainView() { return mainView; }

void UIContext::setMainView(MainView *view) { mainView = view; }

MainView *UIContext::mainView = nullptr;
