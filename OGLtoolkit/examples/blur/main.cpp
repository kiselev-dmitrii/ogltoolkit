#include "lib/Subsystems/Application.h"
#include "BlurTestScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("BlurTestScene");
        app->setScene(new BlurTestScene);

        return app->exec();
}

