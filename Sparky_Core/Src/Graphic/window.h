#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#define MAX_KEYS  1024
#define MAX_BUTTONS  32

namespace Sparky
{
	namespace graphics
	{
		class Window
		{

		private:
			friend struct GLFWwindow;

			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButton[MAX_BUTTONS];
			double mx, my;
		

		public:
			Window(const char* name, int width, int height);
			~Window();
			bool Closed() const;
			void Update();
			void Clear() const;

			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }
			
			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;

		private:
			bool Init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}