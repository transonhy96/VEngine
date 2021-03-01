#pragma once
#include "../Config.h"
#include <GLFW/glfw3.h>
namespace V {

	class V_API Time {

	public:
		static Time* Instance();
		static double deltaTime();
		static void Tick();
	private:
		static Time* s_instance;
		double s_currentFrame;
		double s_lastFrame;
		double s_deltaTime;
		Time();
		~Time();
	};
}