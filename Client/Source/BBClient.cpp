// Filename: BBClient.cpp
// Author: Gael Huber
#include "BBClient.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

namespace BlockBlock
{
	/**
	 * Default constructor
	 */
	Client::Client()
	{

	}

	/**
	 * Destructor
	 */
	Client::~Client()
	{

	}

	// TEMP
	static void error_callback(int error, const char* description)
	{
		fputs(description, stderr);
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	// END TEMP

	/**
	 * Initialize the client
	 * @return Returns true if the initialization is successful
	 */
	bool Client::Initialize()
	{
		// Create the connection manager to manage all incoming messages
		_connectionManager = new ConnectionManager();
		if(_connectionManager->Initialize(0) == false)
		{
			return false;
		}

		// Create the player
		NetAddress address = NetAddress(127, 0, 0, 1, 30000);
		_player = new NetworkPlayer();
		//if(_player->Initialize(address) == false)
		//{
		//	return false;
		//}
		
		GLFWwindow* window;
		glfwSetErrorCallback(error_callback);
		
		if(!glfwInit())
		{
			return false;
		}

		window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
		if(!window)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		while(!glfwWindowShouldClose(window))
		{
			float ratio;
			int width, height;

			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float) height;

			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
			glMatrixMode(GL_MODELVIEW);

			glLoadIdentity();
			glRotatef((float) glfwGetTime() * 50.0f, 0.0f, 0.0f, 1.0f);

			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.6f, -0.4f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.6f, -0.4f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.6f, 0.0f);
			glEnd();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();

		return true;
	}

	/**
	 * Shut down the client
	 */
	void Client::Shutdown()
	{
		if(_connectionManager)
		{
			_connectionManager->Shutdown();
			delete _connectionManager;
			_connectionManager = 0;
		}
	}

	/**
	 * Run the client
	 */
	void Client::Run()
	{
		// Setup the main client loop
		bool isRunning = true;
		while(isRunning)
		{
			// Update the connection manager and receive any messages
			if(_player->Update() == false)
			{
				isRunning = false;
			}
		}
	}

}	// Namespace