#ifndef QDOCKPANEL_H
#define QDOCKPANEL_H

#include <QWidget>

class QDockPanel : public QWidget
{
    Q_OBJECT
public:
    explicit QDockPanel();

    QWidget* getContensWidget(){return contensWidget;}
    QWidget* resetContensWidget(QWidget* newWidget)
   {
        QWidget* old = contensWidget;
        contensWidget = newWidget;
        resetContensWidgetPosAndSize();

        return old;
    }

signals:

public slots:

private:
    int titleRectHeight;    // panel窗口的标题栏的高度.
    QRect titleRect;        // panel窗口的标题栏的位置.
    QWidget* contensWidget; // panel窗口内的widget.
    int frameWidth;         // 边框的宽度.
    bool isPresedTitle;     // 是否在标题栏中按下了鼠标左键.
    QPoint diffPos;         // 鼠标按下时鼠标的位置和窗口位置的差值.


protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent* e);
    void resetContensWidgetPosAndSize();
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent* e);
};

#endif // QDOCKPANEL_H
