#include "Window.h"

namespace V{

    Window::Window() {
        s_window = nullptr;
        b_isInit= false;
        s_width = 800;
        s_height = 600;
        s_ratio = (float)(s_width /s_height);
        b_shouldClose = true;
        s_title = "VEngine";

    }
    Window::~Window() {
        glfwTerminate();
    }

    //callback
	static void glfwWindowResize_CB(GLFWwindow* window, int w, int h) {
		glViewport(0, 0, w, h);
	};
	static void key_CB(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
        if (action == GLFW_PRESS) {
            Keyboard::Instance()->setKey(key);
        }
	}
	void mouseButton_CB(GLFWwindow* window, int button, int action, int mods)
	{
        Mouse::Instance()->setKey(button, action);
	}
	static void cursorPosition_CB(GLFWwindow* window, double xpos, double ypos)
	{
        Mouse::Instance()->setPosition(xpos, ypos);
	}
	void scroll_CB(GLFWwindow* window, double xoffset, double yoffset)
	{
        Mouse::setZoom(yoffset);
	}
    bool Window::Create(const int w,const int h, const char* title = "VEngine") {
        if(init() > 0){

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

            s_width = w;
            s_height = h;
            s_title = title;
            s_window = glfwCreateWindow(s_width, s_height, s_title, nullptr, nullptr);

            glfwSetInputMode(s_window, GLFW_CURSOR, 0);

            Mouse::Instance()->setCursorStartPos((float)s_width / 2, (float)s_height /2);

            if (!s_window)
            {
                glfwTerminate();
            }

            b_isInit = true;

            glfwMakeContextCurrent(s_window);
            
            glfwSetFramebufferSizeCallback(s_window, glfwWindowResize_CB);
            glfwSetKeyCallback(s_window, key_CB);
            glfwSetMouseButtonCallback(s_window, mouseButton_CB);
            glfwSetCursorPosCallback(s_window, cursorPosition_CB);
            glfwSetScrollCallback(s_window, scroll_CB);
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return false;
			}
			glViewport(0, 0, s_width, s_height);

            return true;
        }
        return false;
    }
    bool Window::IsInitialized() const {
        return b_isInit;
    }

    int Window::Height() const {
        return s_height;
    }

    int Window::Width() const {
        return s_width;
    }

    float Window::Ratio() const {
        return s_ratio;
    }

    int Window::init() {

		if (!glfwInit())
			return -1;
        return 1;
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(s_window);
    }

    void Window::swapBuffer() const {
        glfwSwapBuffers(s_window);
    }
   
	void Window::clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
    
}
