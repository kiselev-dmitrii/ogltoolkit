TEMPLATE = app
QT += opengl
LIBS += -lGLEW
LIBS += -lassimp

INCLUDEPATH = ../..

SOURCES += main.cpp \
    ../../lib/OGL/GpuProgram.cpp \
    ../../lib/OGL/VertexArray.cpp \
    ../../lib/OGL/VertexBuffer.cpp \
    ../../lib/OGL/AbstractScene.cpp \
    ../../lib/OGL/UniformBuffer.cpp \
    ../../lib/OGL/BufferObject.cpp \
    ../../lib/OGL/IndexBuffer.cpp \
    ../../lib/Data/Mesh.cpp \
    ../../lib/Utils/StringUtils.cpp \
    QtView.cpp \
    LightScene.cpp

HEADERS += \
    ../../lib/Debug/Debug.h \
    ../../lib/OGL/GpuProgram.h \
    ../../lib/OGL/VertexArray.h \
    ../../lib/OGL/VertexBuffer.h \
    ../../lib/OGL/AbstractScene.h \
    ../../lib/OGL/UniformBuffer.h \
    ../../lib/OGL/BufferObject.h \
    ../../lib/OGL/IndexBuffer.h \
    ../../lib/Data/Mesh.h \
    ../../lib/Utils/StringUtils.h \
    QtView.h \
    LightScene.h

OTHER_FILES += \
    shaders/lighting.vert \
    shaders/lighting.frag

