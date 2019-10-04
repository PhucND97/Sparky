#include "window.h"


namespace Sparky
{
	namespace graphics
	{
		
		void window_resize(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char* title, int width, int height)
			: m_Title(title), m_Width(width), m_Height(height)
		{
			if (!Init())
				glfwTerminate();

			// Init keys and button arrays
			for (int i = 0; i < MAX_KEYS; i++)
				m_Keys[i] = false;

			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseButton[i] = false;
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::Init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to init GLFW\n";
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window)
			{
				glfwTerminate();
				std::cout << "Failed to create GLFW\n";
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to init GLEW\n";
				return false;
			}

			std::cout << "OpenGL" << glGetString(GL_VERSION) << '\n';

			return true;

		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			// TODO: Log this!
			if (button >= MAX_BUTTONS) return false;
			return m_MouseButton[button];
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			// TODO: Log this!
			if (keycode >= MAX_KEYS) return false;
			return m_Keys[keycode];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update()
		{
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}


		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = (action != GLFW_RELEASE);
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButton[button] = (action != GLFW_RELEASE);
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
	}
}