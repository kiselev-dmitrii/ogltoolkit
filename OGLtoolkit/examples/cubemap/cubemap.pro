TEMPLATE = app
LIBS += -lGL
LIBS += -lglfw
LIBS += -lGLEW
LIBS += -lassimp
LIBS += -lIL
LIBS += -lILU

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
    ../../lib/Utils/StreamUtils.cpp \
    ../../lib/Framework/Camera.cpp \
    ../../lib/Framework/Entity.cpp \
    ../../lib/Framework/Render.cpp \
    ../../lib/Subsystems/Application.cpp \
    ../../lib/Subsystems/Mouse.cpp \
    ../../lib/Data/Image.cpp \
    ../../lib/OGL/Texture.cpp \
    ../../lib/OGL/Texture2D.cpp \
    ../../lib/OGL/TextureUnit.cpp \
    ../../lib/OGL/TextureCube.cpp \
    TestScene.cpp

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
    ../../lib/Utils/StreamUtils.h \
    ../../lib/Framework/Camera.h \
    ../../lib/Framework/Entity.h \
    ../../lib/Framework/Render.h \
    ../../lib/Subsystems/Application.h \
    ../../lib/Subsystems/Mouse.h \
    ../../lib/Data/Image.h \
    ../../lib/OGL/Texture.h \
    ../../lib/OGL/Texture2D.h \
    ../../lib/OGL/TextureUnit.h \
    ../../lib/OGL/TextureCube.h \
    TestScene.h

OTHER_FILES += \
#    shaders/lighting.vert \
#    shaders/lighting.frag \
#    shaders/vertLighting.frag \
#    shaders/vertLighting.vert \
#    shaders/multiLighting.frag \
#    shaders/multiLighting.vert \
    bin/resources/shaders/multiFragLighting.vert \
    bin/resources/shaders/multiFragLighting.frag \
    bin/resources/shaders/normalMapping.vert \
    bin/resources/shaders/normalMapping.frag \
    bin/resources/shaders/cubeMapping.vert \
    bin/resources/shaders/cubeMapping.frag

