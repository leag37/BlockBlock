// Filename: BBWindow.h
// Author: Gael Huber
#ifndef __BBWINDOW_H__
#define __BBWINDOW_H__

#include "BBPlatform.h"

#include <GLFW/glfw3.h>

namespace BlockBlock
{
	/**
	 * 	\addtogroup Client
	 * 	@{
	 */
	
	class Window
	{
	public:
		/**
		 * Construct a window from the given width and height
		 * @param width The window's width
		 * @param height The window's height
		 */
		explicit Window(uint width, uint height);

		/**
		 * Destruct the window
		 */
		~Window();

		/**
		 * @return The GLFW window
		 */
		GLFWwindow* GetWindow() const;

		/**
		 * @return Window width
		 */
		uint GetWidth() const;

		/**
		 * @return Window height
		 */
		uint GetHeight() const;

	private:
		/**
		 * GLFW window
		 */
		GLFWwindow* _window;
		
		/**
		 * The window width
		 */
		uint _width;

		/**
		 * The window height
		 */
		uint _height;
	};
	
	/** @} */
}

#endif // __BBWINDOW_H__