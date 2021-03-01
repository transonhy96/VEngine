#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "../Config.h"
#include "../Inputs/Keyboard.h"
#include "../Inputs/Mouse.h"
#include "../Utils/ReadFile.h"
#include <iostream>
namespace V{
    class V_API Window {
    private:
        GLFWwindow* s_window;
        bool b_isInit;
        const char* s_title;
        int s_width;
        int s_height;
        float s_ratio;
        int init();
        bool b_shouldClose;
    public:
        Window();
        ~Window();
        bool Create(int w,int h, const char *title);
        bool IsInitialized() const;
        int Width() const;
        int Height() const;
        float Ratio() const;
        bool ShouldClose() const;
        void swapBuffer() const;
        void clear() const;
        GLFWwindow* getWindowPtr() { return s_window; };
    };
}
