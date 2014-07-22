#ifndef QDOCKFRAME_H
#define QDOCKFRAME_H

#include <QtWidgets>
#include "QDockCommon.h"
#include "QDockArrows.h"

class QDockFrame : public QWidget
{
    Q_OBJECT

public:
    QDockFrame(QWidget *parent = 0);
    virtual ~QDockFrame();
    void showArrow();

private:
    QDockArrows arrows;
};

#endif // QDOCKFRAME_H
