#include "Mouse.h"
#include <GL/glfw.h>

void Mouse::setPos(const ivec2 &pos) { glfwSetMousePos(pos.x, pos.y); }

void Mouse::setPos(int x, int y) { glfwSetMousePos(x, y); }

ivec2 Mouse::pos() {
        ivec2 pos;
        glfwGetMousePos(&pos.x, &pos.y);
        return pos;
}

void Mouse::hide() { glfwDisable(GLFW_MOUSE_CURSOR); }
void Mouse::show() { glfwEnable(GLFW_MOUSE_CURSOR); }
