#include "QDockFrame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDockFrame w;
    w.resize(700,700);
    w.showArrow();
    w.show();

    return a.exec();
}
