#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const std::string&, const std::string);
	~Shader();

	GLuint GetUniform(const std::string& name);
	template<typename T> void SetUniform(const std::string& name, const T& t)
	{
		static_assert(false, "Type is not integrated in shader class");
	}
	template<> void SetUniform<glm::vec1>(const std::string&, const glm::vec1&);
	template<> void SetUniform<glm::vec2>(const std::string&, const glm::vec2&);
	template<> void SetUniform<glm::vec3>(const std::string&, const glm::vec3&);
	template<> void SetUniform<glm::vec4>(const std::string&, const glm::vec4&);
	template<> void SetUniform<glm::mat4>(const std::string&, const glm::mat4&);
	template<> void SetUniform<bool>(const std::string&, const bool&);

	void Clear();

	void Bind();
	static void Unbind();

private:
	static std::unordered_map<unsigned int, GLuint> m_ShaderCache;
	std::unordered_map<std::string, GLuint> m_UniformCache;
	GLuint m_RendererID;

	GLuint CreateProgram(const std::string&, const std::string&);
	GLuint CompileShader(GLenum, const std::string&);
	const std::string ParseShader(const std::string&);
};

