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
