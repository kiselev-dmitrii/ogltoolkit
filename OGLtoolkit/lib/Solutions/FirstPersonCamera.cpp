#include "FirstPersonCamera.h"
#include "lib/Subsystems/Mouse.h"
#include "lib/Subsystems/Keyboard.h"
#include "lib/Subsystems/Application.h"

FirstPersonCamera::FirstPersonCamera(SceneNode *node) : AbstractCamera(node) {
        m_mouseSensitivity = 40;
        m_speedMovement = 5;

        //Изначально камера повернута вниз - поворачиваем, чтобы избежать этот эффект
        m_node->rotateInLocal(vec3(1,0,0), 90);
}

void FirstPersonCamera::setMouseSensitivity(float sensitivity) {
        m_mouseSensitivity = sensitivity;
}

float FirstPersonCamera::mouseSensitivity() const {
        return m_mouseSensitivity;
}

void FirstPersonCamera::setSpeedOfMovement(float speed) {
        m_speedMovement = speed;
}

float FirstPersonCamera::speedOfMovement() const {
        return m_speedMovement;
}

void FirstPersonCamera::update(float deltaTime) {
        updateOrientation(deltaTime);
        updatePosition(deltaTime);
}

void FirstPersonCamera::updateOrientation(float deltaTime) {
        ivec2 pos = Mouse::pos();
        Mouse::setPos(Application::window()->center());
        vec2 delta = vec2(Application::window()->center() - pos);
        rotateWithMouse(delta*deltaTime*m_mouseSensitivity);
}

void FirstPersonCamera::updatePosition(float deltaTime) {
        if(Keyboard::isKeyPressed('W'))  moveForward(m_speedMovement*deltaTime);
        if(Keyboard::isKeyPressed('S'))  moveForward(-m_speedMovement*deltaTime);
        if(Keyboard::isKeyPressed('D'))  moveRight(m_speedMovement*deltaTime);
        if(Keyboard::isKeyPressed('A'))  moveRight(-m_speedMovement*deltaTime);
}
