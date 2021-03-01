#include "Application.h"

namespace V{

    Application::Application() {
        s_window = new Window();
    }

    Application::~Application() {
        dispose();
    }

    void Application::run() {

        init(800, 600,"VEngine");

        glClearColor(0.3f, 0.3f, 0.4f,1.0f);
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum number of vertex attributes supported: " << nrAttributes
			<< std::endl;
		
		// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		
		int width, height, nrChannels;
		unsigned char* data = load_texture("C:/Users/trans/Desktop/thantai.png", &width, &height,
			&nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		// camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		

		glEnable(GL_DEPTH_TEST);

		free_texture_mem(data);
        Shader basic_shader = Shader();
		
        while (!s_window->ShouldClose())
        {
			Time::Instance()->Tick();

			if (glfwGetKey(s_window->getWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(s_window->getWindowPtr(), true);
			//std::cout << "(" << Mouse::Instance()->getVertical() << "," << Mouse::Instance()->getHorizontal() << ")" << std::endl;
			yaw += Mouse::Instance()->getHorizontal();
			pitch += Mouse::Instance()->getVertical();
			FRotator rotator = FRotator(pitch, yaw,0);
			cameraFront = glm::normalize(rotator.getForwardVector());
			std::cout << "(" << cameraFront.x << "," << cameraFront.y << "," << cameraFront.z << ")" << std::endl;

			float cameraSpeed = 2.5 * Time::Instance()->deltaTime();
			if (glfwGetKey(s_window->getWindowPtr(), GLFW_KEY_W) == GLFW_PRESS)
				cameraPos += cameraSpeed * cameraFront;
			if (glfwGetKey(s_window->getWindowPtr(), GLFW_KEY_S) == GLFW_PRESS)
				cameraPos -= cameraSpeed * cameraFront;
			if (glfwGetKey(s_window->getWindowPtr(), GLFW_KEY_A) == GLFW_PRESS)
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			if (glfwGetKey(s_window->getWindowPtr(), GLFW_KEY_D) == GLFW_PRESS)
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


            glfwPollEvents();
            s_window->clear();
			//Wire frame
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glBindTexture(GL_TEXTURE_2D, texture);
			basic_shader.bind();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(-55.0f),
				glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 view = glm::mat4(1.0f);
			// note that we’re translating the scene in the reverse direction
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			glm::mat4 projection;
			projection = glm::perspective(glm::radians(Mouse::getZoom()), 800.0f / 600.0f, 0.1f,
				100.0f);

			

			// camera/view transformation
			glm::mat4 viewCam = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			int viewCamLoc = glGetUniformLocation(basic_shader.ID, "view");
			glUniformMatrix4fv(viewCamLoc, 1, GL_FALSE, glm::value_ptr(viewCam));
			int modelLoc = glGetUniformLocation(basic_shader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			/*int viewLoc = glGetUniformLocation(basic_shader.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));*/
			
			int projectionLoc = glGetUniformLocation(basic_shader.ID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
           
            render();
            /* Swap front and back buffers */
            s_window->swapBuffer();

            /* Poll for and process events */
            
            update();
        }
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
    }

    void Application::init(const int w,const int h, const std::string title) {
        createWindow(w,h,title.c_str());
		Mouse::Instance()->setSensitivity(0.1f);
    }

    void Application::render() {

       

    }

    void Application::update() {

    }

    void Application::dispose() {
        std::cout << "Application being disposed!\n";
        delete s_window;
        s_window = nullptr;
    }
    bool Application::createWindow(const int w,const int h,const char *title) {
       return s_window->Create(w,h,title);
    }
	
}