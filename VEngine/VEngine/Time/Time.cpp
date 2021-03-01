#include "Time.h"

namespace V {

	Time* Time::s_instance = nullptr;

	Time* Time::Instance()
	{
		if (s_instance == nullptr) {
			s_instance = new Time();
		}
		return s_instance;
	}
	double Time::deltaTime(){
		return s_instance->s_deltaTime;
	}
	void Time::Tick() {
		s_instance->s_currentFrame = glfwGetTime();
		s_instance->s_deltaTime = s_instance->s_currentFrame - s_instance->s_lastFrame;
		s_instance->s_lastFrame = s_instance->s_currentFrame;
	}
	Time::~Time()
	{
		delete s_instance;
	}
	Time::Time() {
	}
}