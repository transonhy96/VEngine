#include "Mouse.h"

namespace V {

	Mouse* Mouse::s_instance = nullptr;

	Mouse::Mouse() {
		s_firstMouse = true;
		s_zoom = 45.f;//fov
		s_zoomSpeed = 1.0f;
		s_yoffset = 0.0f;
		s_xoffset = 0.0f;
		s_sensitivity = 0.1f;

	}
	Mouse::~Mouse() {
		delete s_instance;
	}

	void Mouse::setSensitivity(const float& s) {
		s_instance->s_sensitivity = s;
	}
	Mouse* Mouse::Instance()
	{
		if (s_instance == nullptr) {
			s_instance = new Mouse();
		}
		return s_instance;
	}

	bool Mouse::isLeftClick()
	{
		return s_instance->s_MouseButtons[GLFW_MOUSE_BUTTON_LEFT];
	}

	bool Mouse::isRightClick()
	{
		return s_instance->s_MouseButtons[GLFW_MOUSE_BUTTON_RIGHT];
	}

	bool Mouse::isDoubleClick()
	{
		return s_instance->s_MouseButtons[GLFW_MOUSE_BUTTON_LEFT];
	}

	void Mouse::setKey(int button, int action)
	{
		s_instance->s_MouseButtons[button] = action == GLFW_PRESS;
	}

	void Mouse::setPosition(float xpos, float ypos)
	{
		//std::cout << "(" << s_instance->s_xoffset << "," << s_instance->s_yoffset << ")" << std::endl;
		//std::cout << "(" << xpos << "," << ypos << ")" << std::endl;
		if (s_instance->s_firstMouse)
		{
			setCursorStartPos(xpos, ypos);
			s_instance->s_firstMouse = false;
		}

		float xoffset = xpos - s_instance->s_lastX;
		float yoffset = s_instance->s_lastY - ypos; // reversed: y ranges bottom to top
		//std::cout << "(" << xoffset << "," << yoffset << ")" << std::endl;
		setCursorStartPos(xpos, ypos);
		s_instance->s_xoffset *= s_instance->s_sensitivity;
		s_instance->s_yoffset *= s_instance->s_sensitivity;
		std::cout << "(" << s_instance->s_xoffset << "," << s_instance->s_yoffset << ")" << std::endl;
	}
	void Mouse::setCursorStartPos(float xpos, float ypos)
	{
		s_instance->s_lastX = xpos;
		s_instance->s_lastY = ypos;
	}
	void Mouse::getPosition(float& xpos, float& ypos)
	{
		xpos = s_instance->s_lastX;
		ypos = s_instance->s_lastY;
	}


}