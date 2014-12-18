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

QDockFrame::QDockFrame(QDockManager* manager,QWidget *parent)
    : QWidget(parent),arrows_(this),manager_(manager),lastMaskArea_(NoneArea)
{
	rootNode_ = new QDockNode(this);
	maskWidget_ = new QDockMaskWidget(this);
	maskWidget_->hide();

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



void QDockFrame::dragEnterEvent( QDragEnterEvent* e )
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

void QDockFrame::dragMoveEvent( QDragMoveEvent* e )
{
	DockArea area = arrows_.getDockAreaByPos(mapFromGlobal(QCursor::pos()));
	if (area != lastMaskArea_)
	{
		maskWidget_->showOnDockArea(area);
		lastMaskArea_ = area;
	}
	e->accept();
}

void QDockFrame::dragLeaveEvent( QDragLeaveEvent* e )
{
	arrows_.show(NoneArea);
	e->accept();
}

void QDockFrame::dropEvent( QDropEvent* e )
{
	const QMimeData* mimeData = e->mimeData();
	QByteArray ba = mimeData->data("dockpanellib/dockdata");
	QDockDataBuilder builder;
	builder.fromByteArray(ba);

	QDockPanel* panel = qobject_cast<QDockPanel*>(builder.getWidget());
	if (panel && lastMaskArea_ != NoneArea)
	{
		manager_->dockPanelToFrame(panel,lastMaskArea_);
		e->accept();
	}
	else
	{
		e->ignore();
	}

	lastMaskArea_ = NoneArea;
	arrows_.show(NoneArea);
	maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::resizeEvent( QResizeEvent * )
{
	relayout();
}

void QDockFrame::relayout()
{
	rootNode_->setGeometry(rect());
	if (!rootNode_->isVisible())
	{
		rootNode_->show();
	}
}
