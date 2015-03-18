#include "QDockFrame.h"
#include <QDrag>
#include <QMimeData>
#include "QDockNode.h"
#include "QDockMaskWidget.h"
#include <QByteArray>
#include <QDataStream>
#include "QDockPanel.h"
#include "QDockDataBuilder.h"
#include "QDockManager.h"
#include <QLayout>
#include "QDockSideButton.h"
#include "QDockSideBar.h"

QDockFrame::QDockFrame(QDockManager* manager, QWidget *parent)
	: QWidget(parent), arrows_(this), manager_(manager), lastMaskArea_(NoneArea)
{
	maskWidget_ = new QDockMaskWidget(this);
	maskWidget_->hide();

	QVBoxLayout* vlay = new QVBoxLayout(this);
	QHBoxLayout* hlay = new QHBoxLayout;
	
	rootNode_ = new QDockNode(this);

	leftBar_ = new QDockSideBar(this);
	leftBar_->setOrientation(Qt::Vertical);
	rightBar_ = new QDockSideBar(this);
	rightBar_->setOrientation(Qt::Vertical);
	topBar_ = new QDockSideBar(this);
	topBar_->setOrientation(Qt::Horizontal);
	bottomBar_ = new QDockSideBar(this);
	bottomBar_->setOrientation(Qt::Horizontal);

	vlay->addWidget(topBar_);
	vlay->addLayout(hlay);
	vlay->addWidget(bottomBar_);
	hlay->addWidget(leftBar_);
	hlay->addWidget(rootNode_);
	hlay->addWidget(rightBar_);

	vlay->setMargin(0);
	hlay->setMargin(0);

	leftBar_->hide();
	rightBar_->hide();
	topBar_->hide();
	bottomBar_->hide();

	setAcceptDrops(true);
}

QDockFrame::~QDockFrame()
{

}

void QDockFrame::showArrow()
{
	if (rootNode_->count() == 0)
	{
		arrows_.show(CenterArea);
	}
	else
	{
		arrows_.show(LeftArea | TopArea | RightArea | BottomArea);
	}
}



void QDockFrame::dragEnterEvent(QDragEnterEvent* e)
{
	const QMimeData* mimeData = e->mimeData();
	if (mimeData && mimeData->hasFormat("dockpanellib/dockdata"))
	{
		showArrow();
		e->accept();
	}
	else
	{
		e->ignore();
	}
}

void QDockFrame::dragMoveEvent(QDragMoveEvent* e)
{
	DockArea area = arrows_.getDockAreaByPos(mapFromGlobal(QCursor::pos()));
	if (area != lastMaskArea_)
	{
		maskWidget_->showOnDockArea(area);
		lastMaskArea_ = area;
	}
	e->accept();
}

void QDockFrame::dragLeaveEvent(QDragLeaveEvent* e)
{
	if (!rect().contains(mapFromGlobal(QCursor::pos())))
	{
		arrows_.show(NoneArea);
	}
	lastMaskArea_ = NoneArea;
	maskWidget_->showOnDockArea(NoneArea);
	e->accept();
}

void QDockFrame::dropEvent(QDropEvent* e)
{
	const QMimeData* mimeData = e->mimeData();
	if (!mimeData->hasFormat("dockpanellib/dockdata"))
	{
		e->ignore();
		return;
	}
	QByteArray ba = mimeData->data("dockpanellib/dockdata");
	QDockDataBuilder builder;
	builder.fromByteArray(ba);

	QDockPanel* panel = qobject_cast<QDockPanel*>(builder.getWidget());
	if (panel && lastMaskArea_ != NoneArea)
	{
		e->accept();
		manager_->dockPanelTo(panel, this, lastMaskArea_);
	}
	else
	{
		e->ignore();
	}

	lastMaskArea_ = NoneArea;
	arrows_.show(NoneArea);
	maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::onDragEnterPanel()
{
	showArrow();
	maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::onDragLeavePanel()
{
	if (!rect().contains(mapFromGlobal(QCursor::pos())))
	{
		arrows_.show(NoneArea);
	}
	lastMaskArea_ = NoneArea;
	maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::onEndDragAtPanel()
{
	arrows_.show(NoneArea);
	lastMaskArea_ = NoneArea;
	maskWidget_->showOnDockArea(NoneArea);
}

QDockSideButton* QDockFrame::addSideButton(const QString& title, DockArea area)
{
	QDockSideButton* btn = new QDockSideButton(title,this);
	btn->setCheckable(true);

	switch (area)
	{
	case CenterTopArea:
	case TopArea:
		if (topBar_->isHidden())
		{
			topBar_->show();
		}
		topBar_->addWidget(btn);
		break;
	case CenterRightArea:
	case RightArea:
		btn->setOrientation(Qt::Vertical);
		btn->setMirrored(true);
		if (rightBar_->isHidden())
		{
			rightBar_->show();
		}
		rightBar_->addWidget(btn);
		break;
	case CenterBottomArea:
	case BottomArea:
		if (bottomBar_->isHidden())
		{
			bottomBar_->show();
		}
		bottomBar_->addWidget(btn);
		break;
	case NoneArea:
	case LeftArea:
	case CenterArea:
	case CenterLeftArea:
	default:
		btn->setOrientation(Qt::Vertical);
		if (leftBar_->isHidden())
		{
			leftBar_->show();
		}
		leftBar_->addWidget(btn);
		break;
	}

	return btn;
}

