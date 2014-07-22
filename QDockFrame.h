#ifndef QDOCKFRAME_H
#define QDOCKFRAME_H

#include <QtWidgets>

class QDockFrame : public QSplitter
{
    Q_OBJECT

public:
    QDockFrame(QWidget *parent = 0);
    ~QDockFrame();
};

#endif // QDOCKFRAME_H
