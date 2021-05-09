#include "Window.h"

#include "Log.h"
#include "Input.h"

bool Window::isRunning = false;

Window::Window()
	: window(nullptr), m_Width(WIDTH), m_Height(HEIGHT), m_BufferWidth(0), m_BufferHeight(0),
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
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Close()
{
	glfwSetWindowShouldClose(Get()->window, GL_TRUE);
	isRunning = true;
}

Vector2 Window::GetMousePosition() const
{
	double x, y;
	glfwGetCursorPos(Window::Get()->window, &x, &y);
	return Vector2(x/WIDTH, -y/HEIGHT);
}

Vector2 Window::GetMousePositionInWorld(const Camera* camera) const
{
	return Vector2::Zero;
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

	window = glfwCreateWindow(m_Width, m_Height, NAME, nullptr, nullptr);
	if (!window)
	{
		Logger::Print("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(window, &m_BufferWidth, &m_BufferHeight);

	// Set context for GLEW
	glfwMakeContextCurrent(window);

	// Handle Callbacks (key | Mouse)
	CreateCallbacks();

	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		Logger::Print("GLEW initialization failed");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, m_BufferWidth, m_BufferHeight);

	glfwSetWindowUserPointer(window, this);
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(window, Input::HandleKeys);
	glfwSetCursorPosCallback(window, Input::HandleMouse);
}

void Window::EndFrame()
{
	Input::posDelta = Vector2(0.0f, 0.0f); 
}

