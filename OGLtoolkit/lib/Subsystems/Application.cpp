#include "Application.h"
#include "lib/Debug/Debug.h"

Window::Window() {
        m_context.samples = 4;
        m_context.majorVersion = 4;
        m_context.minorVersion = 0;
        m_context.profile = GLFW_OPENGL_CORE_PROFILE;

        m_size = ivec2(0,0);
        m_pos = ivec2(0,0);
        m_title = "No title";
        m_isFullscreen = false;
        m_isOpened = false;
}

Window::~Window() {
        glfwCloseWindow();
}

void Window::setTitle(const string &title) {
        m_title = title;
        if(m_isOpened) glfwSetWindowTitle(m_title.c_str());
}

string Window::title() {
        return m_title;
}

void Window::setSize(const ivec2 &size) {
        m_size = size;
        if(m_isOpened) glfwSetWindowSize(m_size.x, m_size.y);
}

ivec2 Window::size() {
        glfwGetWindowSize(&m_size.x, &m_size.y);
        return m_size;
}

void Window::setPos(const ivec2 &pos) {
        m_pos = pos;
        if(m_isOpened) glfwSetWindowPos(m_pos.x, m_pos.y);
}

ivec2 Window::pos() {
        return m_pos;
}

void Window::setFullscreen(bool value) {
        if(!m_isOpened) m_isFullscreen = value;
        else DEBUG("Window already opened. Please close window, set fullscreen and open again");

}

bool Window::fullscreen() {
        return m_isFullscreen;
}

ivec2 Window::center() {
        return size()/2;
}

bool Window::openWindow() {
        glfwOpenWindowHint(GLFW_FSAA_SAMPLES, m_context.samples);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, m_context.majorVersion);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, m_context.minorVersion);
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE, m_context.profile);

        if(!glfwOpenWindow(m_size.x, m_size.y, 0,0,0,32,32,32, m_isFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW)) {
                DEBUG("Failed to open GLFW window");
                glfwTerminate();
                return false;
        }
        glfwSetWindowTitle(m_title.c_str());
        m_isOpened = true;

        return true;
}

//========================================================================//

auto_ptr<AbstractScene> Application::m_scene;
Window Application::m_window;

Application::Application() {
}

Window *Application::window() {
        return &m_window;
}

void Application::setScene(AbstractScene *scene) {
        m_scene.reset(scene);
}

AbstractScene* Application::scene() {
        return m_scene.get();
}

bool Application::init() {
        if(!m_scene.get()) {
                DEBUG("Scene was not assigned");
                return false;
        }

        if(!glfwInit()) {
                DEBUG("Failed to initialize GLFW");
                return false;
        }

        if(!m_window.openWindow()) {
                DEBUG("Failed to open window");
                return false;
        }

        if(glewInit() != GLEW_OK) {
                DEBUG("Failed to initialize GLEW");
                return false;
        }

        glfwEnable(GLFW_KEY_REPEAT);
        glfwEnable(GLFW_STICKY_KEYS);

        //Инициализация сцены
        m_scene->init();

        // Установка колбэков
        glfwSetWindowSizeCallback(onResizeScene);

        return true;
}

void Application::loop() {
        float oldTime, curTime;
        int running = GL_TRUE;

        oldTime = glfwGetTime();
        // Цикл, пока не закрыли окно
        while(running) {
                curTime = glfwGetTime();
                m_scene->update(curTime-oldTime);
                oldTime = curTime;

                m_scene->render();

                glfwSwapBuffers();
                running = glfwGetWindowParam(GLFW_OPENED);
        }
}

void Application::terminate() {
        glfwTerminate();
}

void Application::onResizeScene(int width, int height) {
        Application::scene()->resize(width, height);
}

int Application::exec() {
        if(!init()) {
                DEBUG("Cannot init application");
                return -1;
        }
        loop();
        terminate();
        return 0;
}
