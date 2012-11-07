#include "lib/Subsystems/Application.h"
#include "LightScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("SpotLighting test");
        app->setScene(new LightScene());

        return app->exec();
}

