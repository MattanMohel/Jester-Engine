#include "Shader.h"
#include "../Core/Log.h"
#include "RendererBase.h"

std::unordered_map<unsigned int, GLuint> Shader::m_ShaderCache;

Shader::Shader(const std::string& vPath, const std::string fPath)
{
	unsigned int hash = STR_HASH(vPath) + STR_HASH(fPath);
	if (m_ShaderCache.find(hash) == m_ShaderCache.end())
		m_ShaderCache[hash] = CreateProgram(ParseShader(vPath), ParseShader(fPath));
	
	m_RendererID = m_ShaderCache[hash];
}

Shader::~Shader()
{
	Clear();
}

GLuint Shader::GetUniform(const std::string& name)
{
	if (m_UniformCache.find(name) != m_UniformCache.end())
		return m_UniformCache[name];
	else
	{
		GLuint id = glGetUniformLocation(m_RendererID, name.c_str());
		m_UniformCache[name] = id;
	}
}

template<> void Shader::SetUniform<glm::vec1>(const std::string& name, const glm::vec1& vec1)
{
	glUniform1fv(GetUniform(name), 1, &vec1.x);
}
template<> void Shader::SetUniform<glm::vec2>(const std::string& name, const glm::vec2& vec2)
{
	glUniform2fv(GetUniform(name), 1, glm::value_ptr(vec2));
}
template<> void Shader::SetUniform<glm::vec3>(const std::string& name, const glm::vec3& vec3)
{
	glUniform3fv(GetUniform(name), 1, glm::value_ptr(vec3));
}
template<> void Shader::SetUniform<glm::vec4>(const std::string& name, const glm::vec4& vec4)
{
	glUniform4fv(GetUniform(name), 1, glm::value_ptr(vec4));
}
template<> void Shader::SetUniform<glm::mat4>(const std::string& name, const glm::mat4& mat4)
{
	glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, glm::value_ptr(mat4));
}
template<> void Shader::SetUniform<bool>(const std::string& name, const bool& state)
{
	glUniform1i(GetUniform(name), state);
}


void Shader::Clear()
{
	if (m_RendererID != 0)
	{
		glDeleteProgram(m_RendererID);
		m_RendererID = 0;
	}
}

void Shader::Bind()
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
	glLinkProgram(0);
}

GLuint Shader::CreateProgram(const std::string& vShader, const std::string& fShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

GLuint Shader::CompileShader(GLenum type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const GLchar* code = source.c_str();
	glShaderSource(id, 1, &code, nullptr);
	glCompileShader(id);

	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLint length = strlen(source.c_str());
		char* message = new char[length];

		glGetShaderInfoLog(id, length, &length, message);
		Logger::Print(LogFlag::Error, "Error compiling the ", type, "shader: ", message);
		delete[] message;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

const std::string Shader::ParseShader(const std::string& path)
{
	struct stat buffer;
	if (!(stat(path.c_str(), &buffer) == 0))
		Logger::Print(LogFlag::Warning, "error opening file");

	std::ifstream stream(path);

	std::string source, line;
	while (getline(stream, line))
	{
		source += line;
		source += "\n";
	}

	return source;
}
