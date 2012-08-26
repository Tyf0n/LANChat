#include <QtGui/QApplication>
#include "lanchatwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LANChatWindow w;
    w.show();
    
    return a.exec();
}
