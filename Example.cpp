#include <iostream>

#include "Example.h"

void Example::handleGUIEvent(GUIEvent evt){
   // Javascript is trying to tell us something :)
   std::cout << "Event from js: " << evt.name << " " << evt.value << "\n";
}

void Example::guiDidLoad(){
   // Everything within WebKit is ready.
   std::cout << "HTML Did Load!" << "\n";

   // Let's send a message to js:
   GUIEvent e;
   e.name = "An event";
   e.value = 2.0;
   window->triggerGUIEvent(e);
}
