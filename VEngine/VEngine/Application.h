#pragma once

#include "Config.h"
#include "Window/Window.h"
#include <string>
#include <iostream>
#include "Loggers/Logger.h"
#include "Shaders/Shader.h"
#include <stdio.h>
#include <iostream>
#include "Utils/TextureLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Time/Time.h"
#include "Maths/FRotator.h"
#include "Inputs/Mouse.h"
namespace V{
    class V_API Application{
    private:
        Window* s_window;
		float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		float pitch = 0.0f;
        void init(int w,int h,const std::string title);
        void render();
        void update();
        void dispose();
    public:
        Application();
        virtual ~Application();
        void run();
        bool createWindow(int w,int h,const char* title);
    };
}