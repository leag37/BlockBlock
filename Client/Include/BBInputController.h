// Filename: BBInputController.h 
// Author: Gael Huber
#ifndef __BBINPUTCONTROLLER_H__
#define __BBINPUTCONTROLLER_H__

#include <GLFW/glfw3.h>

#include "BBPlatform.h"
#include "BBWindow.h"

namespace BlockBlock
{
	/** \addtogroup
	 * 	@{
	 */
	
	class InputController // : public Controller
	{
	public:
		/**
		 * Default constructor
		 */
		InputController();

		/**
		 * Destructor
		 */
		~InputController();

		/**
		 * @return Returns true if initialization is successful
		 */
		bool Initialize();

		/**
		 * Shut down the input controller
		 */
		void Shutdown();

		/**
		 * Bind a window to this input controller
		 */
		void BindWindow(Window* window);

	private:
		/**
		 * The render window registered with this input
		 */
		Window* _window;

	};

	/** @} */
}

#endif