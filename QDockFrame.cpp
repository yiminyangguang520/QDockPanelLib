#include "QDockFrame.h"

QDockFrame::QDockFrame(QWidget *parent)
    : QWidget(parent),arrows(this)
{
}

QDockFrame::~QDockFrame()
{

}

void QDockFrame::showArrow()
{
    arrows.show(Left | Top | Right | Bottom);
}

QDockPanel *QDockFrame::AddPanel(const QString &title,QPoint pos,QSize size, QWidget *contensWidget)
{
    QDockPanel* p = new QDockPanel;
    p->setWindowTitle(title);
    p->resetContensWidget(contensWidget);
    p->move(pos);
    p->resize(size);
    p->show();

    return p;
}
