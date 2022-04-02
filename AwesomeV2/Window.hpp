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
		bool vertical_synchronization;

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

		GLFWwindow* GetWindow() {
			return window;
		}

		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

		~Aws_Window() {
			glfwTerminate();
		}
	};

	typedef Aws_Window Window;
}