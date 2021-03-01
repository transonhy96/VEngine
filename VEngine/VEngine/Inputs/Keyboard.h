#pragma once
#include "../Config.h"
#include "../Loggers/Logger.h"
namespace V {
	
#define MAX_KEYS 348
	
	class V_API Keyboard {
		
	public:
		static Keyboard* Instance();
		static bool isKeyPressed(unsigned int key);
		static void setKey(unsigned int key);
	private:
		static Keyboard* s_instance;
		bool s_Keys[MAX_KEYS] = {0};
		Keyboard();
		~Keyboard();
	};

}