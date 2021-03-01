#include "Shader.h"
namespace V {

	Shader::Shader(const std::string& vertPath, const std::string& fragPath)
	{
		s_id = load(vertPath, fragPath);
		ID = s_id;
	}

	Shader::~Shader() {
		glDeleteProgram(s_id);
	}

	void Shader::bind() const
	{
		glUseProgram(s_id);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	void Shader::setUniform1f(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(s_id, name.c_str()), value);
	}

	void Shader::setUniform1i(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(s_id, name.c_str()), value);
	}

	void Shader::setUniform2f(const std::string& name, const glm::vec2& vec)
	{
		glUniform2f(glGetUniformLocation(s_id, name.c_str()), vec.x,vec.y);
	}

	void Shader::setUniform3f(const std::string& name, const glm::vec3& vec)
	{
		glUniform3f(glGetUniformLocation(s_id, name.c_str()), vec.x, vec.y,vec.z);
	}
	void Shader::setUniform4f(const std::string& name, const glm::vec4& vec)
	{
		glUniform4f(glGetUniformLocation(s_id, name.c_str()), vec.x, vec.y, vec.z,vec.w);
	}
	void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		//glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE, matrix.length());
	}
	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(s_id,name.c_str()), (int)value);
	}
	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(s_id, name.c_str()), value);
	}
	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(s_id, name.c_str()), value);
	}
	GLuint Shader::load(const std::string& vertPath, const std::string& fragPath)
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSource = readFileString(vertPath);
		std::string fragSource = readFileString(fragPath);

		const char* vertexString = vertSource.c_str();
		const char* fragmentString = fragSource.c_str();


		glShaderSource(vertex, 1, &vertexString, NULL);

		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout<<"Failed to compile vertex \n" << &error[0]<<std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragmentString, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment \n" << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return program;
	}
}
