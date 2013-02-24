#include "lib/Subsystems/Application.h"
#include "BlurTestScene.h"

int main() {
        Application::window()->setSize(ivec2(800,600));
        Application::window()->setTitle("BlurTestScene");
        Application::setScene(new BlurTestScene);

        return Application::exec();
}

