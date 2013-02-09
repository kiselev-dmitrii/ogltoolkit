#include "lib/Subsystems/Application.h"
#include "TestScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(600,600));
        app->window()->setTitle("TestScene");
        app->setScene(new TestScene);

        return app->exec();
}

