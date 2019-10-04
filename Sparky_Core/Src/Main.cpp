#include "Graphic\window.h"
#include "Maths\maths.h"



int main()
{
	using namespace Sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << '\n';

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
	vec4 b(2.0f, 3.0f, 4.0f, 5.0f);

	mat4 position = mat4::translation(vec3(2,3,4));

	while (!window.Closed())
	{
		window.Clear();
		std::cout << (a == b) << '\n';

		#if 1
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		#else 
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		#endif
		window.Update();
	}

	//system("PAUSE");
	return 0;
}