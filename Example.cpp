/**
 helloHTML A C++ example program that uses Webkit, html, css and javascript 
 code as a GUI.

 Copyright (C) 2012 Rafael Vega
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

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
