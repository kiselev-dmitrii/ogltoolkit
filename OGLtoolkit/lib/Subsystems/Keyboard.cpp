#include "Keyboard.h"

bool Keyboard::isKeyPressed(int key) {
        return glfwGetKey(key) == GLFW_PRESS;
}

bool Keyboard::isKeyReleased(int key) {
        return glfwGetKey(key) == GLFW_RELEASE;
}
