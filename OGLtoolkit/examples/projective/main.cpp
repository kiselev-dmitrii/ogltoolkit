#include "lib/Subsystems/Application.h"
#include "TestScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("TestScene");
        app->setScene(new TestScene);

        return app->exec();
}

