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
    arrows.show(Left | Top | Right | Bottom /*| Center*/ | CenterLeft | CenterTop | CenterRight | CenterBottom);
}
