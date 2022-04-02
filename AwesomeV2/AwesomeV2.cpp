#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Core.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Window.hpp"

const float speed = 20.0f;

float w = 0.0f;

float old = 0.0f;

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

aws::Renderer skybox;
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

		/*camDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		camDirection.y = sin(glm::radians(pitch));
		camDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(camDirection);*/

		camera.SetCameraRotation(glm::radians(yaw), glm::radians(pitch), aws::Axis::xy);

		cameraFront = glm::normalize(camera.GetCameraRotation());

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
		playerPos -= glm::vec3(cameraFront.x, 0.0f, cameraFront.z) * speed * aws::time.GetDeltaTime();

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		playerPos += glm::vec3(cameraFront.x, 0.0f, cameraFront.z) * speed * aws::time.GetDeltaTime();

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		playerPos += cameraRight * speed * aws::time.GetDeltaTime();

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		playerPos -= cameraRight * speed * aws::time.GetDeltaTime();

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && inGround)
	{
		acceleration = -2.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && aws::time.GetTime() > old + 2.0f)
	{
		ground.Terminate();

		ground.Init(aws::LoadShader("water.vert", aws::ShadType::vertex), aws::LoadShader("water.frag", aws::ShadType::fragment));
		ground.AddTexture("white.png");
		ground.SetTextureByID(0, 1);
		ground.SetColorByID(0, 0.0f, 0.5f, 0.0f, 1.0f);

		ground.SetScale(10000.0f, 0.1f, 10000.0f);

		old = aws::time.GetTime();
	}

	cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));

	camera.SetCameraPosition(playerPos.x, playerPos.y, playerPos.z);
}

void framebuffer_call(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	projection = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 1000.0f);
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

	if (acceleration < 2.5f)
	{
		acceleration += 5.0f * aws::time.GetDeltaTime();
	}
}

class Wnd : public aws::Window
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

Wnd window;

void Wnd::Start()
{
	glfwSetFramebufferSizeCallback(GetWindow(), framebuffer_call);
	glfwSetCursorPosCallback(GetWindow(), mouse);
	framebuffer_call(GetWindow(), 800, 600);

	//skybox.Init(aws::cubemap_vs, aws::cubemap_fs, true);
	ground.Init(aws::LoadShader("water.vert", aws::ShadType::vertex), aws::LoadShader("water.frag", aws::ShadType::fragment));
	ground2.Init(aws::vs, aws::fs);
	//
	//skybox.SetRendererData(aws::skybox);
	//skybox.SetCubemap({
	//	/*"data/skybox/right.png",
	//	"data/skybox/left.png",
	//	"data/skybox/top.png",
	//	"data/skybox/bottom.png",
	//	"data/skybox/front.png",
	//	"data/skybox/back.png"*/
	//	"data/textures/awesomev2.png",
	//	"data/textures/awesomev2.png",
	//	"data/textures/awesomev2.png",
	//	"data/textures/awesomev2.png",
	//	"data/textures/awesomev2.png",
	//	"data/textures/awesomev2.png"
	//	}
	//);
	ground.SetRendererData(aws::cube);
	ground2.SetRendererData(aws::LoadOBJModel("data/models/awesome.obj"));

#if defined _WIN32
	ground.AddTexture("data/textures/stalin.png");
	ground2.AddTexture("white.png");

#elif defined __linux
	ground.AddTexture("AwesomeV2/data/textures/stalin.png");
	ground2.AddTexture("AwesomeV2/data/textures/awesomev2.png");

#endif

	ground.SetColorByID(0, 0.0f, 0.5f, 0.0f, 1.0f);
	ground.SetScale(10000.0f, 0.1f, 10000.0f);

	ground2.SetScale(10.0f, 10.0f, 10.0f);
	ground2.SetPosition(0.0f, 20.0f, 0.0f);

	playerPos.y = 11.0f;
}

void Wnd::Update()
{
	view = glm::lookAt(camera.GetCameraPosition() + cameraFront, camera.GetCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f));

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

	ground.SetFloatMat4g("u_projectionMatrix", 1U, &projection);
	ground.SetFloatMat4g("u_viewMatrix", 1U, &view);
	ground.SetFloatMat4g("u_transform", 1U, &water_transform);

	ground.SetFloat1("u_passedTime", aws::time.GetTime());
	ground.SetFloat1("u_waterPlaneLength", 1.0f);

	ground.SetFloat4v("u_waveParameters", 4, wave);
	ground.SetFloat2v("u_waveDirections", 4, wave_dir);

	ground2.SetRotation(w * 100.0f, w * 100.0f, w * 100.0f);

	w += 0.01f;

	//skybox.SetPosition(camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);

	//skybox.Render(projection, view);
	ground.Render(projection, view);

	ground2.Render(projection, view);
}

void Wnd::LateUpdate()
{
	input(GetWindow());

	std::future<void> phys = std::async(physics);
}

int main()
{
	window.vertical_synchronization = true;
	window.CreateWindow("Window", 800, 600, nullptr);

	return 0;
}