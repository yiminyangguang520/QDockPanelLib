#ifndef QDOCKFRAME_H
#define QDOCKFRAME_H

#include <QtWidgets>
#include "QDockCommon.h"
#include "QDockArrows.h"
#include <map>

class QDockPanel;
class QDockNode;
class QDockMaskWidget;
class QDockManager;

class QDockFrame : public QWidget
{
    Q_OBJECT

public:
    explicit QDockFrame(QDockManager* manager, QWidget *parent);
    virtual ~QDockFrame();
    void showArrow();

	void relayout();
protected:
	virtual void dragEnterEvent( QDragEnterEvent * );

	virtual void dragMoveEvent( QDragMoveEvent * );

	virtual void dragLeaveEvent( QDragLeaveEvent * );

	virtual void dropEvent( QDropEvent * );

	virtual void resizeEvent( QResizeEvent * );

private:
    QDockArrows arrows_;
	QDockNode* rootNode_;
	QDockMaskWidget* maskWidget_;
	std::map<int,QDockPanel*> dockPanels_;
	QDockManager* manager_;

	DockArea lastMaskArea_;

	friend QDockManager;
};

#endif // QDOCKFRAME_H
