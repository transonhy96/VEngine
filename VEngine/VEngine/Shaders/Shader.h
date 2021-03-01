#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../Config.h"
#include "../Utils/ReadFile.h"

namespace V{

    class V_API Shader
    {
    private:
        GLuint s_id;
    public:
        GLuint ID;
        Shader(const std::string& vertPath = "D:/Projects/VEngine/VEngine/VEngine/Shaders/basic_shader.vert", const std::string& fragPath = "D:/Projects/VEngine/VEngine/VEngine/Shaders/basic_shader.frag");
        ~Shader();
        void bind() const;
        void unbind() const;
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
        void setUniform1f(const std::string& name,float value);
        void setUniform1i(const std::string& name,int value);
		void setUniform2f(const std::string& name,const glm::vec2& vec);
		void setUniform3f(const std::string& name, const glm::vec3& vec);
		void setUniform4f(const std::string& name, const glm::vec4& vec);
        void setUniformMat4(const std::string& name,const glm::mat4& matrix);
    private:
        GLuint load(const std::string& vertPath, const std::string& fragPath);
    };
    
}