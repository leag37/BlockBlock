// Filename: BBInputController.cpp
// Author: Gael Huber
#include "BBInputController.h"

namespace BlockBlock
{
	/**
	 * Handle key input triggered by the render window
	 * @param window   [description]
	 * @param key      [description]
	 * @param scancode [description]
	 * @param action   [description]
	 * @param mods     [description]
	 */
	static void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	/**
	 * Default constructor
	 */
	InputController::InputController()
		:	_window(0)
	{

	}

	/**
	 * Destructor
	 */
	InputController::~InputController()
	{

	}

	/**
	 * @return Returns true if initialization is successful
	 */
	bool InputController::Initialize()
	{
		return true;
	}

	/**
	 * Shut down the input controller
	 */
	void InputController::Shutdown()
	{

	}

	/**
	 * Bind a window to this input controller
	 */
	void InputController::BindWindow(Window* window)
	{
		_window = window;
		glfwSetKeyCallback(_window->GetWindow(), KeyInputCallback);
		//glfwSetScrollCallback(window, scroll_callback);
		//glfwSetCursorPosCallback(window, cursor_position_callback);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}