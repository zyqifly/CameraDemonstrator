#include "demonstratorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DemonstratorWidget w;
    w.show();
    return a.exec();
}
