TEMPLATE = app

LIBS += -lGL
LIBS += -lglfw
LIBS += -lGLEW
LIBS += -lassimp
LIBS += -lIL
LIBS += -lILU

INCLUDEPATH = ../..

SOURCES += main.cpp \
    ../../lib/Core/Data/Image.cpp \
    ../../lib/Core/Data/Mesh.cpp \
    ../../lib/Core/OpenGL/Texture2D.cpp \
    ../../lib/Core/OpenGL/BufferObject.cpp \
    ../../lib/Core/OpenGL/VertexArray.cpp \
    ../../lib/Core/OpenGL/TextureUnit.cpp \
    ../../lib/Core/OpenGL/UniformBuffer.cpp \
    ../../lib/Core/OpenGL/Texture.cpp \
    ../../lib/Core/OpenGL/IndexBuffer.cpp \
    ../../lib/Core/OpenGL/Renderbuffer.cpp \
    ../../lib/Core/OpenGL/GpuProgram.cpp \
    ../../lib/Core/OpenGL/Framebuffer.cpp \
    ../../lib/Core/OpenGL/VertexBuffer.cpp \
    ../../lib/Core/OpenGL/TextureCube.cpp \
    ../../lib/Subsystems/Mouse.cpp \
    ../../lib/Subsystems/Keyboard.cpp \
    ../../lib/Subsystems/Application.cpp \
    ../../lib/Utils/StreamUtils.cpp \
    ../../lib/Utils/StringUtils.cpp \
    ../../lib/Framework/Entity.cpp \
    ../../lib/Framework/Camera.cpp \
    ../../lib/Framework/Render.cpp \
    ../../lib/Framework/Node.cpp \
    BlurTestScene.cpp

HEADERS += \
    ../../lib/Core/Data/Image.h \
    ../../lib/Core/Data/Mesh.h \
    ../../lib/Core/OpenGL/VertexBuffer.h \
    ../../lib/Core/OpenGL/UniformBuffer.h \
    ../../lib/Core/OpenGL/TextureUnit.h \
    ../../lib/Core/OpenGL/Framebuffer.h \
    ../../lib/Core/OpenGL/GpuProgram.h \
    ../../lib/Core/OpenGL/IndexBuffer.h \
    ../../lib/Core/OpenGL/BufferObject.h \
    ../../lib/Core/OpenGL/VertexArray.h \
    ../../lib/Core/OpenGL/TextureCube.h \
    ../../lib/Core/OpenGL/Texture.h \
    ../../lib/Core/OpenGL/Renderbuffer.h \
    ../../lib/Core/OpenGL/Texture2D.h \
    ../../lib/Subsystems/Application.h \
    ../../lib/Subsystems/Mouse.h \
    ../../lib/Subsystems/Keyboard.h \
    ../../lib/Utils/Debug.h \
    ../../lib/Utils/StreamUtils.h \
    ../../lib/Utils/StringUtils.h \
    ../../lib/Framework/Camera.h \
    ../../lib/Framework/AbstractScene.h \
    ../../lib/Framework/Entity.h \
    ../../lib/Framework/Render.h \
    ../../lib/Framework/Node.h \
    BlurTestScene.h

OTHER_FILES += \
    bin/resources/shaders/blur.vert \
    bin/resources/shaders/blur.frag
