#pragma once

#include "Core.hpp"
#include <future>

namespace aws
{
	class Aws_Window
	{
	private:
		GLFWwindow* window;

	public:
		/**
		 * @brief It limits number of frames if set to TRUE ( 60 FPS )
		 * 
		 */
		bool vertical_synchronization;

		/**
		 * @brief Create a Window object
		 * 
		 * @param name Window name
		 * @param width Window width
		 * @param height Window height
		 * @param fullscreen If fullscreen
		 */
		void CreateWindow(const std::string& name, const int& width, const int& height, GLFWmonitor* fullscreen) {
			glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(width, height, name.c_str(), fullscreen, nullptr);

			if (!window)
			{
				glfwTerminate();

				return;
			}

			glfwMakeContextCurrent(window);

			glewExperimental = GL_TRUE;

			if (glewInit() != GLEW_OK)
			{
				glfwTerminate();

				return;
			}

			if (!GLEW_VERSION_4_5)
			{
				glfwTerminate();

				return;
			}

			glEnable(GL_DEPTH_TEST);

			Start();

			while (!glfwWindowShouldClose(window))
			{
				time.CalcDeltaTime();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				Update();

				glfwPollEvents();

				glfwSwapBuffers(window);

				glfwSwapInterval((int)vertical_synchronization);

				LateUpdate();
			}
		}

		/**
		 * @brief Get the Window object
		 * 
		 * @return GLFWwindow* 
		 */
		GLFWwindow* GetWindow() {
			return window;
		}

		/**
		 * @brief Start function called on start
		 * 
		 */
		virtual void Start() {}

		/**
		 * @brief Update function called every frame before frame swap
		 * 
		 */
		virtual void Update() {}

		/**
		 * @brief Late update function called every frame after frame swap
		 * 
		 */
		virtual void LateUpdate() {}

		~Aws_Window() {
			glfwTerminate();
		}
	};

	typedef Aws_Window Window;
}