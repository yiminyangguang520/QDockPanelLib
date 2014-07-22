#include "QDockArrows.h"
#include <QPainter>


class QArrowWidget : public QWidget
{
public:
    explicit QArrowWidget(const char* imgPath, QWidget* parent)
        :QWidget(parent,Qt::FramelessWindowHint),pixmap(imgPath)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        resize(pixmap.size());
    }

private:
    QPixmap pixmap;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,pixmap);
    }
};


QDockArrows::QDockArrows(QWidget *parent)
    :QObject(parent),
      leftWid(new QArrowWidget("://ArrowPics/left.png",parent)),
      rightWid(new QArrowWidget("://ArrowPics/right.png",parent)),
      topWid(new QArrowWidget("://ArrowPics/top.png",parent)),
      bottomWid(new QArrowWidget("://ArrowPics/bottom.png",parent)),
      centerWid(new QArrowWidget("://ArrowPics/center.png",parent)),
      centerLeftWid(new QArrowWidget("://ArrowPics/left.png",parent)),
      centerRightWid(new QArrowWidget("://ArrowPics/right.png",parent)),
      centerTopWid(new QArrowWidget("://ArrowPics/top.png",parent)),
      centerBottomWid(new QArrowWidget("://ArrowPics/bottom.png",parent)),
      parentWid(parent)
{

}

void QDockArrows::show(int pos)
{
    int w = parentWid->width();
    int h = parentWid->height();

    if (pos & Left)
    {
        leftWid->move(0,(h-leftWid->height())/2);
        leftWid->show();
    }
    else
    {
        leftWid->hide();
    }

    if (pos & Right)
    {
        rightWid->move(w-rightWid->width(),(h-rightWid->height())/2);
        rightWid->show();
    }
    else
    {
        rightWid->hide();
    }

    if (pos & Top)
    {
        topWid->move((w-rightWid->width())/2,0);
        topWid->show();
    }
    else
    {
        topWid->hide();
    }

    if (pos & Bottom)
    {
        bottomWid->move((w-rightWid->width())/2,h-bottomWid->height());
        bottomWid->show();
    }
    else
    {
        bottomWid->hide();
    }

    if (pos & Center)
    {
        centerWid->move((w-centerWid->width())/2,(h-leftWid->height())/2);
        centerWid->show();
    }
    else
    {
        centerWid->hide();
    }

    if (pos & CenterLeft)
    {
        centerLeftWid->move((w-centerLeftWid->width())/2-centerLeftWid->width(),(h-centerLeftWid->height())/2);
        centerLeftWid->show();
    }
    else
    {
        centerLeftWid->hide();
    }

    if (pos & CenterRight)
    {
        centerRightWid->move((w-centerRightWid->width())/2+centerRightWid->width(),(h-centerRightWid->height())/2);
        centerRightWid->show();
    }
    else
    {
        centerRightWid->hide();
    }

    if (pos & CenterTop)
    {
        centerTopWid->move((w-centerTopWid->width())/2,(h-centerTopWid->height())/2-centerTopWid->height());
        centerTopWid->show();
    }
    else
    {
        centerTopWid->hide();
    }

    if (pos & CenterBottom)
    {
        centerBottomWid->move((w-centerBottomWid->width())/2,(h-centerBottomWid->height())/2+centerBottomWid->height());
        centerBottomWid->show();
    }
    else
    {
        centerBottomWid->hide();
    }
}
