#include "QDockFrame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDockFrame w;
    w.resize(700,700);
    w.show();

    QWidget* widget = new QWidget;
    widget->setAutoFillBackground(true);
    widget->setPalette(QPalette(Qt::black));
    w.AddPanel("testttt",QPoint(100,100),QSize(200,200),widget);

    return a.exec();
}
