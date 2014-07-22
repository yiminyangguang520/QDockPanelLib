#include "QDockFrame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDockFrame w;
    w.show();

    return a.exec();
}
