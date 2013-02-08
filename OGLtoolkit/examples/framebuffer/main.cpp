#include "lib/Subsystems/Application.h"
#include "FBOTestScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("FBOTestScene");
        app->setScene(new FBOTestScene);

        return app->exec();
}

