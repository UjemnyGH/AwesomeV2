#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Core.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include <future>

const float speed = 20.0f;

float w = 0.0f;

glm::mat4 view = glm::mat4(1.0);
glm::mat4 projection = glm::mat4(1.0);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraRight;
glm::vec3 playerPos = glm::vec3(0.0f, 0.0f, 0.0f);

glm::mat4 water_transform = glm::mat4(1.0);

glm::vec3 camDirection;

float yaw, pitch;
float lyaw, lpitch;
int lastX, lastY;
float acceleration = 1.0f;
bool inGround = false;

aws::Camera camera;

float wave[16] = { 0.05f, 0.02f, 0.3f, 0.2f / (0.05f * 0.02f * 4.0f), 0.05f, 0.02f, 0.3f, 0.2f / (0.05f * 0.02f * 4.0f), 0.05f, 0.02f, 0.3f, 0.2f / (0.05f * 0.02f * 4.0f), 0.05f, 0.02f, 0.3f, 0.2f / (0.05f * 0.02f * 4.0f) };
float wave_dir[8] = { 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

aws::Renderer object1;
aws::Renderer ground;
aws::Renderer ground2;

void mouse(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.2f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch -= yoffset;

		if (pitch > 89.9f)
			pitch = 89.9f;
		if (pitch < -89.9f)
			pitch = -89.9f;

		/*camDirection.x = (cos(glm::radians(yaw)) - sin(glm::radians(yaw)));
		camDirection.z = (cos(glm::radians(yaw)) + sin(glm::radians(yaw)));
		camDirection.y = 1;

		lyaw = camDirection.x;
		lpitch = camDirection.z;
		cameraFront = glm::normalize(camDirection);*/

		camDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		camDirection.y = sin(glm::radians(pitch));
		camDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(camDirection);

		/*camera.SetCameraRotation(pitch, aws::Axis::x);
		camera.SetCameraRotation(yaw, aws::Axis::y);

		cameraFront = glm::normalize(camera.GetCameraRotation());*/

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		playerPos -= cameraFront * speed * aws::time.GetDeltaTime() * glm::vec3(1.0f, 0.0f, 1.0f);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		playerPos += cameraFront * speed * aws::time.GetDeltaTime() * glm::vec3(1.0f, 0.0f, 1.0f);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		playerPos += cameraRight * speed * aws::time.GetDeltaTime() * glm::vec3(1.0f, 0.0f, 1.0f);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		playerPos -= cameraRight * speed * aws::time.GetDeltaTime() * glm::vec3(1.0f, 0.0f, 1.0f);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && inGround)
	{
		acceleration = -2.0f;
	}

	cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));

	camera.SetCameraPosition(playerPos.x, playerPos.y, playerPos.z);
}

void framebuffer_call(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	projection = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 1000.0f);
}

static void glfwError(int id, const char* des)
{
	std::cout << des << '\n';
}

void physics()
{
	playerPos.y -= aws::time.GetDeltaTime() * 20.0f * acceleration;

	inGround = aws::CheckAABBCollision(camera.GetCameraPosition(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10000.0f, 0.1f, 10000.0f))
	|| aws::CheckAABBCollision(camera.GetCameraPosition() - glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f));

	if (inGround)
	{
		playerPos.y += aws::time.GetDeltaTime() * 20.0f * fabs(acceleration);
	}

	if (acceleration < 1.5f)
	{
		acceleration += 5.0f * aws::time.GetDeltaTime();
	}
}

int main()
{
	glfwSetErrorCallback(&glfwError);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "1 Day Graphical Engine Chellange", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();

		return - 2;
	}

	if (!GLEW_VERSION_4_5)
	{
		glfwTerminate();

		return -3;
	}

	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_call);
	glfwSetCursorPosCallback(window, mouse);
	framebuffer_call(window, 800, 600);

	object1.Init(aws::cubemap_vs, aws::cubemap_fs, true);
	ground.Init();
	ground2.Init(aws::vs, aws::fs);

	object1.SetRendererData(aws::cube);
	ground.SetRendererData(aws::cube);
	ground2.SetRendererData(aws::cube);

	//object1.AddTexture("AwesomeV2/white.png");
	ground.AddTexture("AwesomeV2/data/textures/stalin.png");
	ground2.AddTexture("AwesomeV2/data/textures/awesome.png");

	ground.SetColorByID(0, 0.0f, 0.5f, 0.0f, 1.0f);
	ground.SetScale(10000.0f, 0.1f, 10000.0f);

	ground2.SetScale(10.0f, 10.0f, 10.0f);
	ground2.SetPosition(0.0f, 20.0f, 0.0f);
	//object1.SetPosition(0.0f, 2.0f, 0.0f);

	playerPos.y = 11.0f;

	while (!glfwWindowShouldClose(window))
	{
		aws::time.CalcDeltaTime();

		input(window);

		view = glm::lookAt(camera.GetCameraPosition() + cameraFront, camera.GetCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

		//object1.SetColorByID(0, sin(aws::time.GetTime()), cos(aws::time.GetTime()), sin(atan(aws::time.GetTime())), 1.0f);
		//rejestr bazowy, licznik, rejest danych, rejeztry wskaznikowe(wsk. baz., wsk. stosu, wsk. instr.), r. seg., flagi(MF, OF, CF, SF, DF, ZF, IF), operandy(register, memory, stałę instrukcyjne, default), tryby adresowania(bezposredni, pos. przez rej., indexowany, skalowany, relatywny), typydanych(DB, DW, DD, DT)

		/*ground.SetFloatMat4g("u_projectionMatrix", 1U, &projection);
		ground.SetFloatMat4g("u_viewMatrix", 1U, &view);
		ground.SetFloatMat4g("u_transform", 1U, &water_transform);

		ground.SetFloat1("u_passedTime", aws::time.GetTime());
		ground.SetFloat1("u_waterPlaneLength", 10.0f);

		ground.SetFloat4v("u_waveParameters", 4, wave);
		ground.SetFloat2v("u_waveDirections", 4, wave_dir);*/

		ground2.SetColorByID(0, sin(w), cos(w), sin(tan(w)), 1.0f);
		ground2.SetRotation(w * 100.0f, w * 100.0f, w * 100.0f);

		w += 0.01f;

		object1.Render(projection, view);

		ground.Render(projection, view);

		ground2.Render(projection, view);

		std::future<void> phys = std::async(physics);

		glfwPollEvents();

		glfwSwapBuffers(window);

		glfwSwapInterval(1);
	}

	glfwTerminate();

	return 0;
}