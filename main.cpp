#include <QApplication>
#include <QtWebKit>

#include "HTMLWindow.h"
#include "Example.h"

int main(int argv, char **args) {
   QApplication app(argv, args);

   Example* example = new Example();
   HTMLWindow* window = new HTMLWindow(800, 600, "qrc:///html/index.html", example);
   window->show();
   
   return app.exec();
}
