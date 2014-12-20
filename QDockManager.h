#ifndef QDOCKMANAGER_H
#define QDOCKMANAGER_H

#include <QWidget>
#include <map>
#include "QDockCommon.h"

class QDockPanel;
class QDockFrame;
class QDockNode;

class QDockManager : public QObject
{
	Q_OBJECT

public:
	QDockManager(QWidget *parent);
	~QDockManager();

	QDockFrame* getDockFrame(){return dockFrmae_;}
	QDockPanel* addPanel(int id, const QString& title, QPoint pos, QSize size, QWidget* contensWidget = NULL);
	QDockPanel* getDockPanelByID(int id);

	bool dockPanelToFrame(QDockPanel* panel,DockArea area);
	bool dockPanelToPanel(QDockPanel* from,QDockPanel* target, DockArea area);

	bool isRootNode(QDockNode* node);

	void undockPanel(QDockPanel* panel);

private:
	void onDragEnterPanel();
	void onDragLeavePanel();
	void onEndDragAtPanel();
private:
	QDockFrame* dockFrmae_;
	std::map<int,QDockPanel*> dockPanels_;

	friend QDockPanel;
	friend QDockFrame;
};

#endif // QDOCKMANAGER_H
