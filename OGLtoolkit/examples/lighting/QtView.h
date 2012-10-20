#ifndef QTVIEW_H
#define QTVIEW_H

#include <QGLWidget>
#include <QTimer>
#include "lib/OGL/AbstractScene.h"

class QtView : public QGLWidget {
        Q_OBJECT
private:
        AbstractScene*  m_scene;
        QTimer*         m_timer;
protected:
        virtual void    initializeGL();
        virtual void    resizeGL(int w, int h);
        virtual void    paintGL();

public:
        QtView(QWidget *parent=0);

public slots:
        void onTimer();
};

#endif // QTVIEW_H
