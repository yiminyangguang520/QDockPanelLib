#include "QDockMaskWidget.h"

QDockMaskWidget::QDockMaskWidget(QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_InputMethodTransparent);
	setAttribute(Qt::WA_TransparentForMouseEvents);

	setPalette(QColor(0,0,255,100));
	setAutoFillBackground(true);
}

QDockMaskWidget::~QDockMaskWidget()
{

}

void QDockMaskWidget::showOnDockArea( DockArea area )
{
	QRect rc = parentWidget()->rect();
	switch (area)
	{
	case LeftArea:
	case CenterLeftArea:
		rc.setWidth(rc.width()/2);
		break;
	case TopArea:
	case CenterTopArea:
		rc.setHeight(rc.height()/2);
		break;
	case RightArea:
	case CenterRightArea:
		rc.setLeft(rc.left()+rc.width()/2);
		break;
	case BottomArea:
	case CenterBottomArea:
		rc.setTop(rc.top()+rc.height()/2);
		break;
	case CenterArea:
		break;
	default:
		hide();
		return;
	}

	move(rc.topLeft());
	resize(rc.size());
	show();
	raise();
}
