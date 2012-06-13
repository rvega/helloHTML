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

#include <QWebFrame>
#include "HTMLWindow.h"

using namespace std;

/**
 * Constructor
 *
 * @param width 
 * @param height
 * @param htmlFilePath 
 *    The html file must be compiled into the application binary and the url must staert with qrc:///
 * @param delegate 
 *    A subclass of HTMLWindowDelegate. 
 */
HTMLWindow::HTMLWindow(int width, int height, const char* htmlFilePath, HTMLWindowDelegate* delegate):
width(width),
height(height),
htmlFilePath(htmlFilePath),
delegate(delegate)
{
   delegate->setWindow(this);

   window = new QMainWindow();
   window->setMaximumSize(width, height);
   window->setMinimumSize(width, height);

   webView = new QWebView(window);
   webView->resize(width, height);
   webView->load(QUrl(htmlFilePath));
   connectToJS();
   connect( webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(connectToJS()) );
};

/**
 * Destructor
 */
HTMLWindow::~HTMLWindow(){
   delete webView;
   delete window;
}

/**
 * Shows the window on screen
 */
void HTMLWindow::show(){
   window->show();
}

/**
 * Sends an event to the Javascript code within the WebKit instance.
 */
void HTMLWindow::triggerGUIEvent(GUIEvent e){
   QString name = QString::fromUtf8(e.name);
   QString value = QString::number(e.value);
   QString json = "{name:\""+ name +"\", value:"+ value +"}";
   QString js = "ContainerWindow.didReceiveEvent("+ json +"); null;";
   // std::cout << qPrintable(js) << "\n";
   webView->page()->mainFrame()->evaluateJavaScript(js);
}

/**
 * Receives an event from the Javascript code and sends it to the delegate.
 *
 * Note that we could ask WebKit to fire this event for us like 
 * 
 *     connect( webView, SIGNAL(loadFinished(bool)), this, SLOT(guiDidLoad(bool)) );
 * 
 * But we'll wait for javascript to trigger it instead. That gives the html application
 * to initialize itself before we start hitting it with events.
 *
 */
void HTMLWindow::handleGUIEvent(QVariantMap event){
   
   // delegate->handleGUIEvent(e);
}
  
/**
 * Receives a "ready" event from Javascript and sends it to the delegate. 
 */
void HTMLWindow::guiDidLoad(bool ok){
   delegate->guiDidLoad();
}

/**
 * Provides a way for Javascript code to output messages to the outside.
 */
void HTMLWindow::log(QString message){
   std::cout << qPrintable(message) << "\n";
}

/**
 * Exposes this class to the javascript code.
 */
void HTMLWindow::connectToJS(){
   webView->page()->mainFrame()->addToJavaScriptWindowObject(QString("ContainerWindow"), this);
}
