#include "lib/Subsystems/Application.h"
#include "FrameWorkTest.h"

int main() {
        Application::window()->setSize(ivec2(800,600));
        Application::window()->setTitle("FrameWorkTest");
        Application::setScene(new FrameWorkTest);

        return Application::exec();
}

