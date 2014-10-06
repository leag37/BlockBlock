// Filename: BBWindow.cpp
// Author: Gael Huber
#include "BBWindow.h"

namespace BlockBlock
{
	/**
	 * Construct a window from the given width and height
	 * @param width The window's width
	 * @param height The window's height
	 */
	Window::Window(uint width, uint height)
		:	_window(0),
			_width(width),
			_height(height)
	{
		_window = glfwCreateWindow(_width, _height, "Window", NULL, NULL);
	}

	/**
	 * Destruct the window
	 */
	Window::~Window()
	{
		if(_window)
		{
			glfwDestroyWindow(_window);
			_window = 0;
		}
	}

	/**
	 * @return The GLFW window
	 */
	GLFWwindow* Window::GetWindow() const
	{
		return _window;
	}

	/**
	 * @return Window width
	 */
	uint Window::GetWidth() const
	{
		return _width;
	}

	/**
	 * @return Window height
	 */
	uint Window::GetHeight() const
	{
		return _height;
	}
}