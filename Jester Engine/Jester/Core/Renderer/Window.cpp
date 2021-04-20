#include "Window.h"
#include "../Input.h"

#include "../Log.h"

bool Window::isRunning = false;

Window::Window()
	: m_Window(nullptr), m_Width(WIDTH), m_Height(HEIGHT), m_BufferWidth(0), m_BufferHeight(0),
	bgColor(0.0f, 0.0f, 0.0f, 1.0f)
{
	Initialize();
}

Window* Window::Get()
{
	static Window* s_Instance = new Window();
	return s_Instance;
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Close()
{
	glfwSetWindowShouldClose(Get()->m_Window, GL_TRUE);
	isRunning = true;
}

void Window::GLClear()
{
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Window::Initialize()
{
	// Initialize GLFW
	if (glfwInit() == GLEW_OK)
	{
		Logger::Print("GLFW Initlialization failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties + version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Minor define
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_Window = glfwCreateWindow(m_Width, m_Height, NAME, nullptr, nullptr);
	if (!m_Window)
	{
		Logger::Print("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(m_Window, &m_BufferWidth, &m_BufferHeight);

	// Set context for GLEW
	glfwMakeContextCurrent(m_Window);

	// Handle Callbacks (key | Mouse)
	CreateCallbacks();

	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		Logger::Print("GLEW initialization failed");
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		return 1;
	}

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, m_BufferWidth, m_BufferHeight);

	glfwSetWindowUserPointer(m_Window, this);
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(m_Window, Input::HandleKeys);
	glfwSetCursorPosCallback(m_Window, Input::HandleMouse);
}

void Window::EndFrame()
{
	Input::posDelta = glm::vec2(0.0f, 0.0f);
}

