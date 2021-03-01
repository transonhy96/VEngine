
#include <iostream>
#include "VEngine.h"
int main()
{
    V::Application* app = new V::Application();
    app->run();
    delete app;
    app = nullptr;
    return 0;
}
