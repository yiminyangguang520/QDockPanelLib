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
class QDockSideBar;
class QDockSideButton;

class QDockFrame : public QWidget
{
	Q_OBJECT

public:
	explicit QDockFrame(QDockManager* manager, QWidget *parent);
	virtual ~QDockFrame();
	void showArrow();

protected:
	virtual void dragEnterEvent(QDragEnterEvent *);

	virtual void dragMoveEvent(QDragMoveEvent *);

	virtual void dragLeaveEvent(QDragLeaveEvent *);

	virtual void dropEvent(QDropEvent *);

private:
	QDockArrows arrows_;
	QDockNode* rootNode_;
	QDockMaskWidget* maskWidget_;
	std::map<int, QDockPanel*> dockPanels_;
	QDockManager* manager_;

	DockArea lastMaskArea_;

	QDockSideBar* leftBar_;
	QDockSideBar* rightBar_;
	QDockSideBar* topBar_;
	QDockSideBar* bottomBar_;

private:
	void onDragEnterPanel();
	void onDragLeavePanel();
	void onEndDragAtPanel();

private:
	QDockSideButton* addSideButton(const QString& title, DockArea area);
	friend QDockManager;
};

#endif // QDOCKFRAME_H
