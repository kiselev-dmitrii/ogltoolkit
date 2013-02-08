#include "lib/Subsystems/Application.h"
#include "%SCENE_NAME%.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("%SCENE_NAME%");
        app->setScene(new %SCENE_NAME%);

        return app->exec();
}

