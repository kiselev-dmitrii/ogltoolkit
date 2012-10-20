TEMPLATE = app
QT += opengl
LIBS += -lGLEW

INCLUDEPATH = ../..

SOURCES += main.cpp \
    ../../lib/OGL/GpuProgram.cpp \
    ../../lib/OGL/VertexArray.cpp \
    ../../lib/OGL/VertexBuffer.cpp \
    ../../lib/OGL/AbstractScene.cpp \
    QtView.cpp \
    TriangleScene.cpp \
    ../../lib/OGL/UniformBuffer.cpp \
    ../../lib/OGL/IndexBuffer.cpp \
    ../../lib/OGL/BufferObject.cpp

HEADERS += \
    ../../lib/Debug/Debug.h \
    ../../lib/OGL/GpuProgram.h \
    ../../lib/OGL/VertexArray.h \
    ../../lib/OGL/VertexBuffer.h \
    ../../lib/OGL/AbstractScene.h \
    QtView.h \
    TriangleScene.h \
    ../../lib/OGL/UniformBuffer.h \
    ../../lib/OGL/IndexBuffer.h \
    ../../lib/OGL/BufferObject.h

OTHER_FILES += \
    shaders/basic.vert \
    shaders/basic.frag

