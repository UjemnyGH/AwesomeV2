#pragma once

#include "Core.hpp"
#include <future>

namespace aws
{
	enum Aws_Keys
	{
		_0 = GLFW_KEY_0,
		_1 = GLFW_KEY_1,
		_2 = GLFW_KEY_2,
		_3 = GLFW_KEY_3,
		_4 = GLFW_KEY_4,
		_5 = GLFW_KEY_5,
		_6 = GLFW_KEY_6,
		_7 = GLFW_KEY_7,
		_8 = GLFW_KEY_8,
		_9 = GLFW_KEY_9,
		NUM_0 = GLFW_KEY_KP_0,
		NUM_1 = GLFW_KEY_KP_1,
		NUM_2 = GLFW_KEY_KP_2,
		NUM_3 = GLFW_KEY_KP_3,
		NUM_4 = GLFW_KEY_KP_4,
		NUM_5 = GLFW_KEY_KP_5,
		NUM_6 = GLFW_KEY_KP_6,
		NUM_7 = GLFW_KEY_KP_7,
		NUM_8 = GLFW_KEY_KP_8,
		NUM_9 = GLFW_KEY_KP_9,
		NUM_DEC = GLFW_KEY_KP_DECIMAL,
		NUM_DIV = GLFW_KEY_KP_DIVIDE,
		NUM_MUL = GLFW_KEY_KP_MULTIPLY,
		NUM_SUB = GLFW_KEY_KP_SUBTRACT,
		NUM_ADD = GLFW_KEY_KP_ADD,
		NUM_ENTER = GLFW_KEY_KP_ENTER,
		NUM_EQUAL = GLFW_KEY_KP_EQUAL,
		L_SHIFT = GLFW_KEY_LEFT_SHIFT,
		L_ALT = GLFW_KEY_LEFT_ALT,
		L_CTRL = GLFW_KEY_LEFT_CONTROL,
		L_SUPER = GLFW_KEY_LEFT_SUPER,
		R_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		R_ALT = GLFW_KEY_RIGHT_ALT,
		R_CTRL = GLFW_KEY_RIGHT_CONTROL,
		R_SUPER = GLFW_KEY_RIGHT_SUPER,
		MENU = GLFW_KEY_MENU,
		SPACE = GLFW_KEY_SPACE,
		APOSTRO = GLFW_KEY_APOSTROPHE,
		COMMA = GLFW_KEY_COMMA,
		MINUS = GLFW_KEY_MINUS,
		DOT = GLFW_KEY_PERIOD,
		SLASH = GLFW_KEY_SLASH,
		SEMICOLON = GLFW_KEY_SEMICOLON,
		EQUAL = GLFW_KEY_EQUAL,
		L_BRACKET = GLFW_KEY_LEFT_BRACKET,
		R_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		BACKSLASH = GLFW_KEY_BACKSLASH,
		GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
		ESC = GLFW_KEY_ESCAPE,
		ENTER = GLFW_KEY_ENTER,
		TAB = GLFW_KEY_TAB,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		INSERT = GLFW_KEY_INSERT,
		DEL = GLFW_KEY_DELETE,
		RIGHT = GLFW_KEY_RIGHT,
		LEFT = GLFW_KEY_LEFT,
		UP = GLFW_KEY_UP,
		DOWN = GLFW_KEY_DOWN,
		PG_UP = GLFW_KEY_PAGE_UP,
		PG_DOWN = GLFW_KEY_PAGE_DOWN,
		HOME = GLFW_KEY_HOME,
		END = GLFW_KEY_END,
		CAPSLOCK = GLFW_KEY_CAPS_LOCK,
		SCROLLLOCK = GLFW_KEY_SCROLL_LOCK,
		NUMLOCK = GLFW_KEY_NUM_LOCK,
		PRINTSCREEN = GLFW_KEY_PRINT_SCREEN,
		PAUSE = GLFW_KEY_PAUSE,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		W = GLFW_KEY_W,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		Q = GLFW_KEY_Q,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,
		UNKNOWN = GLFW_KEY_UNKNOWN
	};

	enum Aws_KeyState
	{
		PRESS = GLFW_PRESS,
		RELEASE = GLFW_RELEASE,
		REPEAT = GLFW_REPEAT
	};

	enum Aws_CursorState
	{
		LOCKED = GLFW_CURSOR_DISABLED,
		HIDDEN = GLFW_CURSOR_HIDDEN,
		NORMAL = GLFW_CURSOR_NORMAL
	};

	class Aws_Window
	{
	private:
		GLFWwindow* window;

	public:
		//static int width;
		//static int height;

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
		inline GLFWwindow* GetWindow() {
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

		/**
		 * @brief Sets visibility of cursor
		 *
		 * @param state Choose 1 of 3 states (default NORMAL)
		 */
		void SetCursorState(Aws_CursorState state = Aws_CursorState::NORMAL) { glfwSetInputMode(window, GLFW_CURSOR, state); }

		/**
		 * @brief Gets key input
		 * 
		 * @param key Key to check 
		 * @param state Key state to check
		 */
		inline bool GetKey(Aws_Keys key, Aws_KeyState state = Aws_KeyState::PRESS) { return glfwGetKey(window, key) == state; }

		//static int GetWidth() { return width; }
		//static int GetHeight() { return height; }

		~Aws_Window() {
			glfwTerminate();
		}
	};

	typedef Aws_Window Window;
	typedef Aws_Keys Keys;
	typedef Aws_KeyState KeyState;
	typedef Aws_CursorState CursorState;
}