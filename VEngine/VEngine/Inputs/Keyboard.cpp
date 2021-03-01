#include "Keyboard.h"
namespace V {

	Keyboard* Keyboard::s_instance = nullptr;

	Keyboard::Keyboard() {
		
	}
	Keyboard::~Keyboard() {
		delete s_instance;
	}

	
	Keyboard* Keyboard::Instance()
	{
		if (s_instance == nullptr) {
			s_instance = new Keyboard();
		}
		return s_instance;
	}

	bool Keyboard::isKeyPressed(unsigned int key) {
		if (key >= MAX_KEYS) {
			V_CORE_ERROR("Key input out of range");
			return false;
		}
		return s_instance->s_Keys[key];
	}

	void Keyboard::setKey(unsigned int key)
	{
		s_instance->s_Keys[key] = true;
	}


}