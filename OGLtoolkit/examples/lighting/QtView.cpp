#include <GL/glew.h>
#include "lib/Debug/Debug.h"
#include "QtView.h"
#include "LightScene.h"

QtView::QtView(QWidget *parent) : QGLWidget(parent) {
        // Устанавливаем версию и профиль
        format().setVersion(4, 0);
        format().setProfile(QGLFormat::CoreProfile);

        // Установка фокуса, при клике и размеров окна
        this->setFocusPolicy(Qt::ClickFocus);
        this->setMinimumSize(800, 600);

        // Через каждую миллисекунду будет вызываться onTimer
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
        m_timer->start(1);
}

void QtView::initializeGL() {
        //////////////// Здесь требуется указать конкретную сцену //////////////////
        m_scene = new LightScene();
        ////////////////////////////////////////////////////////////////////////////

        // Инициализация GLEW
        GLenum err = glewInit();
        if (err != GLEW_OK) DEBUG("Error initializing GLEW" << glewGetErrorString(err));

        // Инициализация сцены
        m_scene->init();
}

void QtView::resizeGL(int w, int h) {
        m_scene->resize(w, h);
}

void QtView::paintGL() {
        m_scene->render();
}

void QtView::onTimer() {
        m_scene->update(0.0f);
        this->updateGL();
}
