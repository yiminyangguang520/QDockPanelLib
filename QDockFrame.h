#ifndef QDOCKFRAME_H
#define QDOCKFRAME_H

#include <QtWidgets>
#include "QDockCommon.h"
#include "QDockArrows.h"
#include "QDockPanel.h"

class QDockFrame : public QWidget
{
    Q_OBJECT

public:
    QDockFrame(QWidget *parent = 0);
    virtual ~QDockFrame();
    void showArrow();

    QDockPanel* AddPanel(const QString& title, QPoint pos, QSize size, QWidget* contensWidget = NULL);

private:
    QDockArrows arrows;
};

#endif // QDOCKFRAME_H
