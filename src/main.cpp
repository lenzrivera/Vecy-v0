// Once again, here we have a half-cooked finished project :)
// It's functional, but could probably be polished a little bit more.
// Potential improvements are commented throughout the project files.

/* Vector z-indices should have been set better, and colors should have been
   defined maybe within the shaders themselves.*/

#include <ggl.h>

#include "VecyMain.h"

const unsigned int WINDOW_WIDTH = 960;
const unsigned int WINDOW_HEIGHT = 540;

const double SECONDS_PER_FRAME = 1.0 / 60.0;

int main()
{
	// Initialize window and OpenGL context.
	ggl::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Vecy-v0");

	// Initialize OpenGL further.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	// Initialize application + Main Loop
	VecyMain application(window);
	
	double currTime = glfwGetTime();
	double prevTime = currTime;
	double accumulatedTime = 0.0;
	while (!window.shouldClose())
	{
		while (accumulatedTime >= SECONDS_PER_FRAME)
		{
			application.processInput(window, SECONDS_PER_FRAME);
			window.pollEvents();

			accumulatedTime -= SECONDS_PER_FRAME;
		}
		
		application.render(window);	
		
		currTime = glfwGetTime();
		accumulatedTime += currTime - prevTime;
		prevTime = currTime;
	}
	
	return 0;
}