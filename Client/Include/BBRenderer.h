// Filename: BBRenderer.h
// Author: Gael Huber
#ifndef __BBRENDERER_H__
#define __BBRENDERER_H__

#include <GL/glew.h>

#include "BBPlatform.h"
#include "BBVector.h"
#include "BBWindow.h"

namespace BlockBlock
{
	/** \addtogroup Client
	 *	@{
	 */
	
	/**
	 * Renderer is responsible for managing graphics
	 */
	class Renderer
	{
	public:
		/**
		 * Default constructor
		 */
		Renderer();

		/**
		 * Destructor
		 */
		~Renderer();

		/**
		 * Initialize the renderer
		 * @return Returns true if the initialization succeeds
		 */
		bool Initialize();

		/**
		 * Shutdown the renderer
		 */
		void Shutdown();

		/**
		 * Create a window
		 * @param width The window width
		 * @param height The window height
		 */
		Window* CreateWindow(uint width, uint height);

		/**
		 * Set the window as active
		 * @param window The window to set as active
		 */
		void SetActiveWindow(Window* window);

	private:
		/**
		 * The array of created windows
		 */
		Vector<Window*> _windows;

		/**
		 * The active window
		 */
		Window* _activeWindow;
	};

	/** @} */
}

#endif // __BBRENDERER_H__