// Filename: BBClient.cpp
// Author: Gael Huber
#include "BBClient.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

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

	// Position
	glm::vec3 position = glm::vec3(0, 0, 5);

	// Horizontal angle: toward -Z
	float horizontalAngle = 3.14f;

	// Vertical angle: 0, look at horizon
	float verticalAngle = 0.0f;

	// Initial field of fiew
	float initialFoV = 45.0f;

	// Speed of movement
	float speed = 3.0f;
	float mouseSpeed = 0.05f;

	double currentTime = 0.0;
	double lastTime = 0.0;
	float deltaTime = 0.0f;
	float FoV = 45.0f;

	double xPos = 10000.0;
	double yPos = 10000.0;
	double xLast = 10000.0;
	double yLast = 10000.0;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
	{
		//std::cout << "x: " << xOffset << " y: " << yOffset << std::endl;
		FoV -= 5 * yOffset;

		if(FoV < 0.0)
		{
			FoV = 0.0;
		}
		else if(FoV > 180.0)
		{
			FoV = 180.0f;
		}
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		// Initialize x and y
		if(xLast == 10000.0 && yLast == 10000.0)
		{
			xLast = xPos = xpos;
			yLast = yPos = ypos;

		}

		xLast = xPos;
		xPos = xpos;

		yLast = yPos;
		yPos = ypos;

		horizontalAngle += mouseSpeed * deltaTime * float(xLast - xPos);
		verticalAngle += mouseSpeed * deltaTime * float(yLast - yPos);
	}

	// Load shaders
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
	{
		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the vertex shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

		if(VertexShaderStream.is_open())
		{
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}

		// Read the fragment shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

		if(FragmentShaderStream.is_open())
		{
			std::string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile vertex shader
		printf("Compiling shader: %s\n", vertex_file_path);
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check vertex shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

		// Compile fragment shader
		printf("Compiling shader: %s\n", fragment_file_path);
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check vertex shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

		// Linking the program
		fprintf(stdout, "Linking program\n");
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the programs
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ProgramID;
	}

	GLuint loadBMP_custom(const char* imagePath)
	{
		// Data read from the header of the BMP file
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char* data;

		FILE* file = fopen(imagePath, "rb");
		if(!file)
		{
			printf("Image could not be found\n");
		}

		if(fread(header, 1, 54, file) != 54)
		{
			printf("Not a correct BMP file. Header too small.\n");
			return 0;
		}

		if(header[0] != 'B' || header[1] != 'M')
		{
			printf("Not a correct BMP file. Signature invalid.\n");
			return 0;
		}

		// Read ints from the byte array
		dataPos 	= *(int*)&(header[0x0A]);
		imageSize 	= *(int*)&(header[0x22]);
		width 		= *(int*)&(header[0x12]);
		height 		= *(int*)&(header[0x16]);

		// Some BMP files are misformatted so derive missing info
		if(imageSize == 0)
		{
			imageSize = width * height * 3;
		}

		if(dataPos == 0)
		{
			dataPos = 54;
		}

		// Create a buffer
		data = new unsigned char[imageSize];

		// Read the contents from the file into the buffer
		fread(data, 1, imageSize, file);

		// Close the file
		fclose(file);

		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// Bind the newly created texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		// When magnifying the image (no bigger mipmap available), use linear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// When minifying the image, use a linear blend of two mipmaps, each filtered linearly
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Generate mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	GLuint loadDDS(const char* imagePath)
	{
		unsigned char header[124];

		FILE* fp;

		// Try to open the file
		fp = fopen(imagePath, "rb");
		if(fp == NULL)
		{
			return 0;
		}

		// Verify the type of file
		char filecode[4];
		fread(filecode, 1, 4, fp);
		if(strncmp(filecode, "DDS ", 4) != 0)
		{
			fclose(fp);
			return 0;
		}

		// Get the surface desc
		fread(&header, 124, 1, fp);

		unsigned int height 		= *(unsigned int*)&(header[8]);
		unsigned int width 			= *(unsigned int*)&(header[12]);
		unsigned int linearSize 	= *(unsigned int*)&(header[16]);
		unsigned int mipMapCount	= *(unsigned int*)&(header[24]);
		unsigned int fourCC			= *(unsigned int*)&(header[80]);

		unsigned char* buffer;
		unsigned int buffSize;

		// How big is it going to be including all mipmaps?
		buffSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(buffSize * sizeof(unsigned char));
		fread(buffer, 1, buffSize, fp);

		// Close the file pointer
		fclose(fp);

		// Config DXT1-5
		#define MAKEDXT(a, b, c, d) (((unsigned int)a) | ((unsigned int)b << 8) | ((unsigned int)c << 16) | (unsigned int)(d << 24))
		#define FOURCC_DXT1 MAKEDXT('D', 'X', 'T', '1')
		#define FOURCC_DXT3 MAKEDXT('D', 'X', 'T', '3')
		#define FOURCC_DXT5 MAKEDXT('D', 'X', 'T', '5')

		// Support DXT1, DXT3, and DXT5
		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch(fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;

		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;

		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;

		default:
			free(buffer);
			return 0;
		}

		// Create the texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// Bind the newly created texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Populate mipmaps
		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		// Load the mipmaps
		for(unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;
		}

		free(buffer);

		return textureID;
	}

	bool loadOBJ(
		const char* path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
		)
	{
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		FILE* file = fopen(path, "r");
		if(file == NULL)
		{
			printf("Impossible to open the file!\n");
			return false;
		}

		// Read until the file ends
		for(;;)
		{
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if(res == EOF)
				break;

			// Parse the line if valid and not end of file
			if(strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if(strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if(strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if(strcmp(lineHeader, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2]
					);
				if(matches != 9)
				{
					printf("File can't be read by our simple parse :(\n");
					fclose(file);
				}

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		// Process vertices
		for(unsigned int i = 0; i < vertexIndices.size(); ++i)
		{
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
		}

		// Process uvs
		for(unsigned int i = 0; i < uvIndices.size(); ++i)
		{
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			out_uvs.push_back(uv);
		}

		// Process vertices
		for(unsigned int i = 0; i < normalIndices.size(); ++i)
		{
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			out_normals.push_back(normal);
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

		// Hints for antialiasing, etc.
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// We want to use OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Ensure we are using recent OpenGL
		
		window = glfwCreateWindow(1024, 768, "Simple example", NULL, NULL);
		if(!window)
		{
			glfwTerminate();
			return false;
		}

		int wWidth, wHeight;
		glfwGetWindowSize(window, &wWidth, &wHeight);
		std::cout << "Width : " << wWidth << " Height: " << wHeight << std::endl;

		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if(glewInit() != GLEW_OK)
		{
			fprintf(stderr, "Failed to initialize GLEW\n");
			glfwTerminate();
			return false;
		}

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		glfwSetKeyCallback(window, key_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Generate the vertex array object
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Create and compile our GLSL program from the shaders
		GLuint programID = LoadShaders("Media/Shaders/SimpleShader.vs", "Media/Shaders/SimpleShader.ps");

		// Get a handle for our MVP uniform
		GLuint matrixID = glGetUniformLocation(programID, "MVP");

		// Projection matrix: 45 degree field of view, 4:3 ratio, display range 0.1-100 units
		glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		// Camera matrix
		glm::mat4 view = glm::lookAt(
			glm::vec3(4, 3, 3),	// camera is at (4,3,3) in world space
			glm::vec3(0, 0, 0),	// and looks at the origin
			glm::vec3(0, 1, 0)	// head is up
			);

		// Model matrix: an identity matrix (model will be at the origin)
		glm::mat4 model = glm::mat4(1.0f);	// Changes for each model

		// Our MVP matrix
		glm::mat4 mvp = projection * view * model;

		// Load model
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		bool res = loadOBJ("Media/Meshes/cube.obj", vertices, uvs, normals);

		// Create vector of indices
		std::vector<unsigned int> indices;
		for(unsigned int i = 0; i < vertices.size(); ++i)
		{
			indices.push_back(i);
		}
		GLuint elementBuffer;
		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// This will identify our vertex buffer
		GLuint vertexBuffer;

		// Generate 1 buffer, put the result ing identifier in vertexBuffer
		glGenBuffers(1, &vertexBuffer);

		// The following command will talk about our vertexBuffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		
		// Give our vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		GLuint uvBuffer;
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

		// Normals
		GLuint normalBuffer;
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

		//GLuint texture = loadBMP_custom("Media/Textures/uvtemplate.bmp");
		GLuint texture = loadDDS("Media/Textures/uvtemplate.DDS");

		// Get a handle on our myTextureSampler uniform
		GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");

		// Enable depth test
		glEnable(GL_DEPTH_TEST);

		// Accept fragment if it is closer to the camera than the former
		glDepthFunc(GL_LESS);

		// Set timer
		lastTime = glfwGetTime();

		float timeElapsed = 0.0f;
		int frames = 0;
		double xOrigin, yOrigin;
		glfwSetCursorPos(window, 1024.0/2.0, 768.0/2.0);

		// Enable backface culling
		glEnable(GL_CULL_FACE);

		// Frame buffer
		GLuint frameBuffer = 0;
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

		// Create the render texture
		GLuint renderTexture;
		glGenTextures(1, &renderTexture);

		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, renderTexture);

		// Give an empty image to OpenGL (the last 0)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		// Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Depth buffer for render texture
		GLuint depthRenderBuffer;
		glGenRenderbuffers(1, &depthRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

		// Configure frame buffer. Set renderTexture as our color attachment 0
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture, 0);

		// Set the list of draw buffers
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers);

		// Fullscreen quad FBO
		GLuint quad_VertexArrayId;
		glGenVertexArrays(1, &quad_VertexArrayId);
		glBindVertexArray(quad_VertexArrayId);

		static const GLfloat g_quad_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0,
			1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0
		};

		GLuint quad_VertexBuffer;
		glGenBuffers(1, &quad_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, quad_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

		// Create and compile our GLSL program from shaders
		GLuint quad_ProgramID = LoadShaders("Media/Shaders/Passthrough.vs", "Media/Shaders/Passthrough.ps");
		GLuint texID = glGetUniformLocation(quad_ProgramID, "renderTexture");
		GLuint timeId = glGetUniformLocation(quad_ProgramID, "time");

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("Could not configure render target\n");
			return false;
		}

		while(!glfwWindowShouldClose(window))
		{
			// Bind the frame buffer
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			glViewport(0, 0, 1024, 768);

			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Enable the program
			glUseProgram(programID);

			// Send our transformation to the currently bound shader
			// in the MVP uniform
			// For each model you render, sinc ethe mvp will be different
			glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(textureID, 0);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(
				0,			// attribute 0
				3,			// size
				GL_FLOAT,	// type
				GL_FALSE,	// normalized?
				0,			// stride
				(void*)0 	// array buffer offset
				);

			// 2nd attribute buffer: colors
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glVertexAttribPointer(
				1,			// attribute
				2,			// size
				GL_FLOAT,	// type
				GL_FALSE,	// normalized?
				0,			// stride
				(void*)0 	// array buffer offset
				);

			// 3rd attribute buffer: normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
			glVertexAttribPointer(
				2,			// attribute
				3,			// size
				GL_FLOAT,	// type
				GL_FALSE,	// normalized?
				0,			// stride
				(void*)0 	// array buffer offset
				);

			// Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

			// Draw triangles
			glDrawElements(
				GL_TRIANGLES,	// mode
				indices.size(),	// count
				GL_UNSIGNED_INT,// type
				(void*)0 		// element array buffer offset
				);
			// Draw triangle
			//glDrawArrays(GL_TRIANGLES, 0, 3*12);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			// Render to screen
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, 1024 * 2, 768 * 2);

			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// User the shader
			glUseProgram(quad_ProgramID);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, renderTexture);

			// Set our renderTexture sampler to user Texture Unit 0
			glUniform1i(texID, 0);

			glUniform1f(timeId, (float)(glfwGetTime() * 10.0f));

			// First attribute buffer: vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, quad_VertexBuffer);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
				);

			// Draw triangles!
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();

			// Get delta time
			currentTime = glfwGetTime();
			deltaTime = float(currentTime - lastTime);
			lastTime = currentTime;

			// Update frames
			timeElapsed += deltaTime;
			++frames;
			if(timeElapsed >= 1.0f)
			{
				// Output frames
				std::cout << "FPS: " << frames << std::endl;
				frames = 0;
				timeElapsed -= 1.0f;
			}

			// Direction: Spherical coordinates  to Cartesian coordinates
			glm::vec3 direction(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
				);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - 3.14f/2.0f),
				0,
				cos(horizontalAngle - 3.14f/2.0f)
				);
			
			// Move forward
			if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				position += direction * deltaTime * speed;
			}

			// Move backward
			if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				position -= direction * deltaTime * speed;
			}

			// Strafe right
			if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				position += right * deltaTime * speed;
			}

			// Strafe left
			if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				position -= right * deltaTime * speed;
			}

			// Up vector
			glm::vec3 up = glm::cross(right, direction);
			
			projection = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

			// Camera matrix
			view = glm::lookAt(
				position,
				position + direction,
				up
				);

			// Calc updated MVP matrix
			mvp = projection * view * model;
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