#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Core/Vector2.h"
#include "../Core/Color.h"

#include "Camera.h"

#define WIDTH 1920
#define HEIGHT 1080
#define NAME "Jester Engine"

class Window
{
public:
	~Window();

	static bool isRunning;
	static Window* Get();

	inline void SetClearColor(float r, float g, float b) { bgColor = Color(r, g, b, 1); }

	static inline void PollEvents() { glfwPollEvents(); }
	static inline float GetTime() { return glfwGetTime(); }

	Vector2 GetMousePosition() const;
	Vector2 GetMousePositionInWorld(const Camera* camera) const;

	inline float GetBufferWidth() const { return m_BufferWidth; }
	inline float GetBufferHeight() const { return m_BufferHeight; }
	inline void SwapBuffers() const { glfwSwapBuffers(window); }

	/*Deals with executions that need to be handeled at
	the end of the frame*/
	static void EndFrame();

	inline static bool shouldClose() { return isRunning; }
	static void Close();
	void GLClear();

	GLFWwindow* window;

private:
	Window(const Window& w) = delete;
	Window();

	int Initialize();


	float m_Width, m_Height;
	int m_BufferWidth, m_BufferHeight;

	//make a Color struct later
	Color bgColor; 

	void CreateCallbacks();
};

