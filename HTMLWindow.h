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

#pragma once

#include <iostream>
#include <ctime>
#include <QObject>
#include <QString>
#include <QMainWindow>
#include <QWebView>
#include <QVariantMap>

#include "GUIEvent.h"

class HTMLWindow;

/**
 * The HTMLWindowDelegate is a delegation protocol. Subclasses can handle events comming from the Javascript
 * code running within the WebKit instance.
 */
class HTMLWindowDelegate {
   public:
      virtual void handleGUIEvent(GUIEvent evt) = 0;
      virtual void guiDidLoad() = 0;
      virtual void setWindow(HTMLWindow* win){
         window = win;
      }

   protected:
      HTMLWindow* window;
};

/**
 * The HTMLWindow Class encapsulates a WebKit web browser to be used as a GUI canvas and 
 * provides an API to communicate to and from the Javascript code running within it.
 */
class HTMLWindow: public QObject {
   Q_OBJECT
   public:
      HTMLWindow(int width, int height, const char* htmlFilePath, HTMLWindowDelegate* delegate);
      ~HTMLWindow();
      void show(); 
      void triggerGUIEvent(GUIEvent e);

   protected:
      int width;
      int height;
      const char* htmlFilePath;
      HTMLWindowDelegate* delegate;
      QMainWindow* window;
      QWebView* webView;

   protected slots:
      void guiDidLoad(bool ok);
      void connectToJS();
      void log(QString message);
      void handleGUIEvent(QVariantMap event);
};
