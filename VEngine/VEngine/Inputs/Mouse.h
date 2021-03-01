#pragma once
#include "../Config.h"
#include "../Loggers/Logger.h"
#include "GLFW/glfw3.h"
#include <iostream>
namespace V {

#define MAX_BUTTONS 16																	

	class V_API Mouse {
	private:
	    bool s_MouseButtons[MAX_BUTTONS] = {0};
		double s_lastX;
		double s_lastY;
		float s_sensitivity;
		float s_xoffset;
		float s_yoffset;
		float s_zoom;
		bool s_firstMouse;
		float s_zoomSpeed;
		static Mouse* s_instance;
		Mouse();
		~Mouse();
	public:
		static Mouse* Instance();
		static void setSensitivity(const float& s);
		static bool isLeftClick();
		static bool isRightClick();
		static bool isDoubleClick();
		static void setKey(int button, int action);
		static void setCursorStartPos(float xpos, float ypos);
		static void setPosition(float xpos, float ypos);
		static void getPosition(float& xpos, float& ypos);
		static float getVertical() { return s_instance->s_yoffset; };
		static float getHorizontal() { return s_instance->s_xoffset; };

		static void setZoom(float amount) {
			s_instance->s_zoom -= s_instance->s_zoomSpeed * amount;
			if (s_instance->s_zoom < 1.0f)
				s_instance->s_zoom = 1.0f;
		}
		static float getZoom() {
			return s_instance->s_zoom;
		}
	};

}