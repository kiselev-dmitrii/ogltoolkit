#include "lib/Subsystems/Application.h"
#include "ImageLightingScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("ImageLightingScene");
        app->setScene(new ImageLightingScene);

        return app->exec();
}

