#include "DefaultCamera.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Keyboard.h"
#include "lib/Subsystems/Application.h"

void DefaultCamera::updateOrientation(float deltaTime) {
        ivec2 pos = Mouse::pos();
        Mouse::setPos(Application::window()->center());
        vec2 delta = vec2(Application::window()->center() - pos);
        rotateWithMouse(delta*deltaTime*m_mouseSensitivity);
}

void DefaultCamera::updatePosition(float deltaTime) {
        if(Keyboard::isKeyPressed('W'))  moveForward(m_speedMovement*deltaTime);
        if(Keyboard::isKeyPressed('S'))  moveForward(-m_speedMovement*deltaTime);
        if(Keyboard::isKeyPressed('D'))  moveRight(m_speedMovement*deltaTime);
        if(Keyboard::isKeyPressed('A'))  moveRight(-m_speedMovement*deltaTime);
}

DefaultCamera::DefaultCamera(SceneNode *node) : AbstractCamera(node) {
        m_mouseSensitivity = 10;
        m_speedMovement = 5;
}

void DefaultCamera::update(float deltaTime) {
        updateOrientation(deltaTime);
        updatePosition(deltaTime);
}
