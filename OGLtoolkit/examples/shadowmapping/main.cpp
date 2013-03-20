#include "lib/Subsystems/Application.h"
#include "ShadowmapTest.h"

int main() {
        Application::window()->setSize(ivec2(800,600));
        Application::window()->setTitle("ShadowmapTest");
        Application::setScene(new ShadowmapTest);

        return Application::exec();
}

