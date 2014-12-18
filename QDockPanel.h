#ifndef QDOCKPANEL_H
#define QDOCKPANEL_H

#include <QWidget>

#include "QDockPanelComponents.h"

class QDockManager;

class QDockPanel : public QWidget
{
    Q_OBJECT
public:
    explicit QDockPanel(QDockManager* manager,QWidget* frame);

    QWidget* getContensWidget(){return contensWidget_;}
    QWidget* resetContensWidget(QWidget* newWidget)
   {
        QWidget* old = contensWidget_;
        contensWidget_ = newWidget;
        resetContensWidgetPosAndSize();

        return old;
    }

	void setId(int id){id_ = id;}
	int id(){return id_;}

	bool isDocked(){return isDocked_;}
	bool dockTo(QWidget* target = NULL);
	void undock();
private:
	void resizeWidget(int curX,int curY);
	void relayout();
	void setDockStatus();
	void setFloatStatus();

signals:

private:
	int id_;	//panel ID
    int titleRectHeight_;    // panel窗口的标题栏的高度.
    QWidget* contensWidget_; // panel窗口内的widget.
    int edgeWidth_;         // 边框的宽度.
	bool isDocked_;
	QSize floatSize_;
	QDockManager* manager_;

	QDockPanelTitle* title_;
	QDockPanelEdgeLeft* leftEdge_;
	QDockPanelEdgeTop* topEdge_;
	QDockPanelEdgeRight* rightEdge_;
	QDockPanelEdgeBottom* bottomEdge_;
	QDockPanelEdgeLeftTop* leftTopEdge_;
	QDockPanelEdgeRightTop* rightTopEdge_;
	QDockPanelEdgeRightBottom* rightBottomEdge_;
	QDockPanelEdgeLeftBottom* leftBottomEdge_;

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent* e);
    void resetContensWidgetPosAndSize();

	friend QDockManager;
	friend QDockPanelTitle;
};

#endif // QDOCKPANEL_H
