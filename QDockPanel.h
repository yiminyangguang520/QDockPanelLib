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
    int titleRectHeight;
    QRect titleRect;
    QWidget* contensWidget;
    int frameWidth;

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent* e);
    void resetContensWidgetPosAndSize();
};

#endif // QDOCKPANEL_H
