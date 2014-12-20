#include "QDockPanelComponents.h"

#include "QDockPanel.h"
#include "QDockDataBuilder.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

QDockPanelTitle::QDockPanelTitle( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setPalette(QPalette(Qt::lightGray));
	setAutoFillBackground(true);
}

void QDockPanelTitle::paintEvent( QPaintEvent * )
{
	QPainter p(this);
	p.drawText(rect(),Qt::AlignLeft|Qt::AlignVCenter,title_);
}

void QDockPanelTitle::setTitle( const QString& title )
{
	title_ = title;
	repaint();
}

void QDockPanelTitle::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldPos_ = parentWidget()->pos();
	}
}

void QDockPanelTitle::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelTitle::mouseMoveEvent( QMouseEvent* e)
{
	if (!isLBtnPressed_)
	{
		return;
	}

	QDockPanel* panel = qobject_cast<QDockPanel*>(parentWidget());
	if (panel && panel->isDocked_)
	{
		panel->undock();
	}

	if (QApplication::keyboardModifiers ()!= Qt::ControlModifier)
	{
		startDrag();
		return;
	}

	parentWidget()->move(parentOldPos_.x()+e->globalX()-pressedPos_.x(),parentOldPos_.y()+e->globalY()-pressedPos_.y());
}

void QDockPanelTitle::startDrag()
{
	QMimeData* mimeData = new QMimeData;
	QDockDataBuilder data;
	data.setWidget(parentWidget());
	mimeData->setData("dockpanellib/dockdata",data.toByteArray());
	QDrag drag(this);
	QPixmap pic(parentWidget()->size());
	parentWidget()->render(&pic);
	drag.setPixmap(pic);
	drag.setMimeData(mimeData);
	parentWidget()->hide();
	if (drag.start() == Qt::IgnoreAction)
	{
		parentWidget()->move(QCursor::pos());
	}
	parentWidget()->show();
	isLBtnPressed_ = false;
}

QDockPanelEdgeLeft::QDockPanelEdgeLeft( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeHorCursor);
}

void QDockPanelEdgeLeft::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldRect_ = parentWidget()->geometry();
	}
}

void QDockPanelEdgeLeft::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeLeft::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int x,y,w,h;
	x = parentOldRect_.x()+e->globalX()-pressedPos_.x();
	y = parentWidget()->pos().y();
	w = parentOldRect_.width()-(e->globalX()-pressedPos_.x());
	if (w < 20)
	{
		return;
	}
	h = parentWidget()->height();
	parentWidget()->move(x,y);
	parentWidget()->resize(w,h);
}

QDockPanelEdgeTop::QDockPanelEdgeTop( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeVerCursor);
}

void QDockPanelEdgeTop::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldRect_ = parentWidget()->geometry();
	}
}

void QDockPanelEdgeTop::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeTop::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int x,y,w,h;
	x = parentWidget()->pos().x();
	y = parentOldRect_.y()-(pressedPos_.y()-e->globalY());
	w = parentWidget()->width();
	h = parentOldRect_.height()-(e->globalY()-pressedPos_.y());
	if (h < 20)
	{
		return;
	}
	parentWidget()->move(x,y);
	parentWidget()->resize(w,h);
}

QDockPanelEdgeRight::QDockPanelEdgeRight( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeHorCursor);
}

void QDockPanelEdgeRight::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldWidth_ = parentWidget()->width();
	}
}

void QDockPanelEdgeRight::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeRight::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int w,h;
	w = parentOldWidth_-(pressedPos_.x()-e->globalX());
	if (w < 20)
	{
		return;
	}
	h = parentWidget()->height();
	parentWidget()->resize(w,h);
}

QDockPanelEdgeBottom::QDockPanelEdgeBottom( QWidget *parent ) :QWidget(parent)
{
	setCursor(Qt::SizeVerCursor);
}

void QDockPanelEdgeBottom::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldHeight_ = parentWidget()->height();
	}
}

void QDockPanelEdgeBottom::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeBottom::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int w,h;
	w = parentWidget()->width();
	h = parentOldHeight_-(pressedPos_.y()-e->globalY());
	if (h < 20)
	{
		return;
	}
	parentWidget()->resize(w,h);
}

QDockPanelEdgeLeftTop::QDockPanelEdgeLeftTop( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeFDiagCursor);
}

void QDockPanelEdgeLeftTop::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldRect_ = parentWidget()->geometry();
	}
}

void QDockPanelEdgeLeftTop::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeLeftTop::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int x,y,w,h;
	x = parentOldRect_.x()+e->globalX()-pressedPos_.x();
	y = parentOldRect_.y()-(pressedPos_.y()-e->globalY());
	w = parentOldRect_.width()-(e->globalX()-pressedPos_.x());
	if (w < 20)
	{
		w = 20;
		x = parentWidget()->pos().x();
	}
	h = parentOldRect_.height()-(e->globalY()-pressedPos_.y());
	if (h < 20)
	{
		h = 20;
		y = parentWidget()->pos().y();
	}
	parentWidget()->move(x,y);
	parentWidget()->resize(w,h);
}

QDockPanelEdgeRightTop::QDockPanelEdgeRightTop( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeBDiagCursor);
}

void QDockPanelEdgeRightTop::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldRect_ = parentWidget()->geometry();
	}
}

void QDockPanelEdgeRightTop::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeRightTop::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int x,y,w,h;
	x = parentWidget()->pos().x();
	y = parentOldRect_.y()-(pressedPos_.y()-e->globalY());
	w = parentOldRect_.width()-(pressedPos_.x()-e->globalX());
	if (w < 20)
	{
		w = 20;
	}
	h = parentOldRect_.height()-(e->globalY()-pressedPos_.y());
	if (h < 20)
	{
		h = 20;
		y = parentWidget()->pos().y();
	}
	parentWidget()->move(x,y);
	parentWidget()->resize(w,h);
}

QDockPanelEdgeRightBottom::QDockPanelEdgeRightBottom( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeFDiagCursor);
}

void QDockPanelEdgeRightBottom::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldSize_ = parentWidget()->size();
	}
}

void QDockPanelEdgeRightBottom::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeRightBottom::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int w,h;
	w = parentOldSize_.width()-(pressedPos_.x()-e->globalX());
	if (w < 20)
	{
		w = 20;
	}
	h = parentOldSize_.height()-(pressedPos_.y()-e->globalY());
	if (h < 20)
	{
		h = 20;
	}
	parentWidget()->resize(w,h);
}

QDockPanelEdgeLeftBottom::QDockPanelEdgeLeftBottom( QWidget *parent ) :QWidget(parent),isLBtnPressed_(false)
{
	setCursor(Qt::SizeBDiagCursor);
}

void QDockPanelEdgeLeftBottom::mousePressEvent( QMouseEvent* e )
{
	if (e->button() == Qt::LeftButton)
	{
		isLBtnPressed_ = true;
		pressedPos_ = e->globalPos();
		parentOldRect_ = parentWidget()->geometry();
	}
}

void QDockPanelEdgeLeftBottom::mouseReleaseEvent( QMouseEvent* )
{
	isLBtnPressed_ = false;
}

void QDockPanelEdgeLeftBottom::mouseMoveEvent( QMouseEvent* e )
{
	if (!isLBtnPressed_)
	{
		return;
	}

	int x,y,w,h;
	x = parentOldRect_.x()+e->globalX()-pressedPos_.x();
	y = parentWidget()->pos().y();
	w = parentOldRect_.width()-(e->globalX()-pressedPos_.x());
	if (w < 20)
	{
		w = 20;
		x = parentWidget()->pos().x();
	}
	h = parentOldRect_.height()-(pressedPos_.y()-e->globalY());
	if (h < 20)
	{
		h = 20;
	}
	parentWidget()->move(x,y);
	parentWidget()->resize(w,h);
}
