#include "QDockTabBar.h"
#include <QDebug>
#include <QMouseEvent>

QDockTabBar::QDockTabBar(QWidget *parent)
    :QTabBar(parent),isLButtonDown_(false),sendDragOut_(false)
{
}

QDockTabBar::~QDockTabBar()
{

}



void QDockTabBar::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        isLButtonDown_ = true;
        sendDragOut_ = false;
    }
    QTabBar::mousePressEvent(e);
}

void QDockTabBar::mouseReleaseEvent(QMouseEvent *e)
{
    isLButtonDown_ = false;
    QTabBar::mouseReleaseEvent(e);
}

void QDockTabBar::mouseMoveEvent(QMouseEvent *e)
{
	QTabBar::mouseMoveEvent(e);
    if (isLButtonDown_ && !rect().contains(e->pos()))
    {
        if (!sendDragOut_)
        {
            emit dragTabOut(currentIndex());
            sendDragOut_ = true;
        }
        return;
    }
}
