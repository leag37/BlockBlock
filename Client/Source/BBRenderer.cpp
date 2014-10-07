// Filename: BBRenderer.cpp
// Author: Gael Huber
#include "BBRenderer.h"

#include <iostream>

namespace BlockBlock
{
	/**
	 * Default constructor
	 */
	Renderer::Renderer()
		:	_activeWindow(0)
	{

	}

	/**
	 * Destructor
	 */
	Renderer::~Renderer()
	{

	}

	/**
	 * Initialize the renderer
	 * @return Returns true if the initialization succeeds
	 */
	bool Renderer::Initialize()
	{
		// Initialize GLFW
		if(glfwInit() == false)
		{
			return false;
		}

		// Configure GLFW
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// We want to use OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Ensure we are using recent OpenGL

		// Initialize GLEW
		glewExperimental = true;

		return true;
	}

	/**
	 * Shutdown the renderer
	 */
	void Renderer::Shutdown()
	{
		// Delete all existing windows
		if(_activeWindow)
		{
			_activeWindow = 0;
		}
		while(_windows.Empty() == false)
		{
			Window* window = _windows.Last();
			_windows.PopBack();
			delete window;
		}

		// Shutdown GLFW
		glfwTerminate();
	}

	/**
	 * Update the renderer
	 * @return Returns true if the renderer updates successfully
	 */
	bool Renderer::Update()
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Swap the window buffer
		glfwSwapBuffers(_activeWindow->GetWindow());

		// Poll for GLFW events
		glfwPollEvents();

		return true;
	}

	/**
	 * Create a window
	 * @param width The window width
	 * @param height The window height
	 */
	Window* Renderer::CreateWindow(uint width, uint height)
	{
		Window* window = new Window(width, height);
		_windows.PushBack(window);
		return window;
	}

	/**
	 * Set the window as active
	 * @param window The window to set as active
	 */
	void Renderer::SetActiveWindow(Window* window)
	{
		_activeWindow = window;
		glfwMakeContextCurrent(_activeWindow->GetWindow());

		// Initialize GLEW for this new context
		if(glewInit() != GLEW_OK)
		{
			// Output?
		}

		// Set the clear color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
}