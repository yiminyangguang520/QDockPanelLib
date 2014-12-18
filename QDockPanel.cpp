#include "QDockPanel.h"
#include <QResizeEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QCursor>
#include <QByteArray>
#include <QDataStream>
#include "QDockDataBuilder.h"
#include "QDockNode.h"
#include <cassert>
#include "QDockFrame.h"
#include "QDockManager.h"
#include "QDockArrows.h"
#include "QDockMaskWidget.h"

QDockPanel::QDockPanel(QDockManager* manager,QWidget* frame)
    :QWidget(frame,Qt::FramelessWindowHint | Qt::Tool),
	manager_(manager),contensWidget_(NULL),
	edgeWidth_(3),titleRectHeight_(20),isDocked_(false)
{
	title_ = new QDockPanelTitle(this);
	connect(this,SIGNAL(windowTitleChanged(const QString&)),title_,SLOT(setTitle(const QString&)));
	leftEdge_ = new QDockPanelEdgeLeft(this);
	leftTopEdge_ = new QDockPanelEdgeLeftTop(this);
	topEdge_ = new QDockPanelEdgeTop(this);
	rightTopEdge_ = new QDockPanelEdgeRightTop(this);
	rightEdge_ = new QDockPanelEdgeRight(this);
	rightBottomEdge_ = new QDockPanelEdgeRightBottom(this);
	bottomEdge_ = new QDockPanelEdgeBottom(this);
	leftBottomEdge_ = new QDockPanelEdgeLeftBottom(this);
}


void QDockPanel::paintEvent(QPaintEvent*)
{
    QPainter p(this);
}

void QDockPanel::resizeEvent(QResizeEvent*)
{
    relayout();
}

void QDockPanel::resetContensWidgetPosAndSize()
{
    if (!contensWidget_)
    {
        return;
    }

    if (contensWidget_->parentWidget() != this)
    {
        contensWidget_->setParent(this);
    }

	if (isDocked_)
	{
		contensWidget_->move(0,edgeWidth_ + titleRectHeight_);
		contensWidget_->resize(width(),height() - edgeWidth_ - titleRectHeight_);
	}
	else
	{
		contensWidget_->move(edgeWidth_,edgeWidth_ * 2 + titleRectHeight_);
		contensWidget_->resize(width() - edgeWidth_ * 2,height() - edgeWidth_ * 3 - titleRectHeight_);
	}
}


void QDockPanel::relayout()
{
	if (isDocked_)
	{
		title_->move(0,0);
		title_->resize(width(),titleRectHeight_);

		leftEdge_->hide();
		leftTopEdge_->hide();
		topEdge_->hide();
		rightTopEdge_->hide();
		rightEdge_->hide();
		rightBottomEdge_->hide();
		bottomEdge_->hide();
		leftBottomEdge_->hide();
	}
	else
	{
		title_->move(edgeWidth_,edgeWidth_);
		title_->resize(width()-edgeWidth_*2,titleRectHeight_);

		leftEdge_->move(0,edgeWidth_);
		leftEdge_->resize(edgeWidth_,height()-edgeWidth_*2);

		leftTopEdge_->move(0,0);
		leftTopEdge_->resize(edgeWidth_,edgeWidth_);

		topEdge_->move(edgeWidth_,0);
		topEdge_->resize(width()-edgeWidth_*2,edgeWidth_);

		rightTopEdge_->move(width()-edgeWidth_,0);
		rightTopEdge_->resize(edgeWidth_,edgeWidth_);

		rightEdge_->move(width()-edgeWidth_,edgeWidth_);
		rightEdge_->resize(edgeWidth_,height()-edgeWidth_*2);

		rightBottomEdge_->move(width()-edgeWidth_,height()-edgeWidth_);
		rightBottomEdge_->resize(edgeWidth_,edgeWidth_);

		bottomEdge_->move(edgeWidth_,height()-edgeWidth_);
		bottomEdge_->resize(width()-edgeWidth_*2,edgeWidth_);

		leftBottomEdge_->move(0,height()-edgeWidth_);
		leftBottomEdge_->resize(edgeWidth_,edgeWidth_);
	}

	resetContensWidgetPosAndSize();
}

void QDockPanel::setDockStatus()
{
	floatSize_ = size();
	setWindowFlags(Qt::SubWindow);
	relayout();
	isDocked_ = true;
}

void QDockPanel::setFloatStatus()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	resize(floatSize_);
	relayout();
	isDocked_ = false;
}

bool QDockPanel::dockTo( QWidget* target /*= NULL*/ )
{
	return false;
}

void QDockPanel::undock()
{
	manager_->undockPanel(this);
}
