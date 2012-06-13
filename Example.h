#pragma once

#include "HTMLWindow.h"

class Example: public HTMLWindowDelegate{
protected:
   void handleGUIEvent(GUIEvent evt);
   void guiDidLoad();
};

