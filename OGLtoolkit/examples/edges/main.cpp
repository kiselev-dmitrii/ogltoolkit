#include "lib/Subsystems/Application.h"
#include "EdgeTestScene.h"

int main() {
        Application *app = Application::instance();

        app->window()->setSize(ivec2(800,600));
        app->window()->setTitle("EdgeTestScene");
        app->setScene(new EdgeTestScene);

        return app->exec();
}

