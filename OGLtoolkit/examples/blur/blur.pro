TEMPLATE = app

LIBS += -lGL
LIBS += -lglfw
LIBS += -lGLEW
LIBS += -lassimp
LIBS += -lIL
LIBS += -lILU

INCLUDEPATH = ../..

SOURCES += main.cpp \
    ../../lib/Subsystems/Mouse.cpp \
    ../../lib/Subsystems/Keyboard.cpp \
    ../../lib/Subsystems/Application.cpp \
    ../../lib/Utils/StreamUtils.cpp \
    ../../lib/Utils/StringUtils.cpp \
    ../../lib/OGL/Texture2D.cpp \
    ../../lib/OGL/BufferObject.cpp \
    ../../lib/OGL/VertexArray.cpp \
    ../../lib/OGL/TextureUnit.cpp \
    ../../lib/OGL/UniformBuffer.cpp \
    ../../lib/OGL/Texture.cpp \
    ../../lib/OGL/IndexBuffer.cpp \
    ../../lib/OGL/Renderbuffer.cpp \
    ../../lib/OGL/GpuProgram.cpp \
    ../../lib/OGL/Framebuffer.cpp \
    ../../lib/OGL/VertexBuffer.cpp \
    ../../lib/OGL/TextureCube.cpp \
    ../../lib/Data/Image.cpp \
    ../../lib/Data/Mesh.cpp \
    ../../lib/Framework/Entity.cpp \
    ../../lib/Framework/Camera.cpp \
    ../../lib/Framework/Render.cpp \
    BlurTestScene.cpp

HEADERS += \
    ../../lib/Debug/Debug.h \
    ../../lib/Subsystems/Application.h \
    ../../lib/Subsystems/Mouse.h \
    ../../lib/Subsystems/Keyboard.h \
    ../../lib/Utils/StreamUtils.h \
    ../../lib/Utils/StringUtils.h \
    ../../lib/OGL/VertexBuffer.h \
    ../../lib/OGL/UniformBuffer.h \
    ../../lib/OGL/TextureUnit.h \
    ../../lib/OGL/Framebuffer.h \
    ../../lib/OGL/GpuProgram.h \
    ../../lib/OGL/IndexBuffer.h \
    ../../lib/OGL/AbstractScene.h \
    ../../lib/OGL/BufferObject.h \
    ../../lib/OGL/VertexArray.h \
    ../../lib/OGL/TextureCube.h \
    ../../lib/OGL/Texture.h \
    ../../lib/OGL/Renderbuffer.h \
    ../../lib/OGL/Texture2D.h \
    ../../lib/Data/Image.h \
    ../../lib/Data/Mesh.h \
    ../../lib/Framework/Camera.h \
    ../../lib/Framework/Entity.h \
    ../../lib/Framework/Render.h \
    BlurTestScene.h

OTHER_FILES += \
    bin/resources/shaders/blur.vert \
    bin/resources/shaders/blur.frag
