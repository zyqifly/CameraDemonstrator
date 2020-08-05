#include "camerademonstatorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraDemonstatorWidget w;
    w.show();
    return a.exec();
}
