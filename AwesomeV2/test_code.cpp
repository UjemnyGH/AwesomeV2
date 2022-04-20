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
#include "CollisionHandler.hpp"

aws::CollisionHandler ch;

class Wnd : public aws::Window
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	void input();
};

const float normal_speed = 40.0f;
const float speed_mul = 2.0f;

float speed = normal_speed;

float w = 0.0f;

float old = 0.0f;

glm::mat4 view = glm::mat4(1.0);
glm::mat4 projection = glm::mat4(1.0);
aws::Vector cameraFront = { 0.0f, 0.0f, -1.0f };
aws::Vector cameraRight;
aws::Vector playerPos = aws::Vector(0.0f, 0.0f, 0.0f);

float yaw, pitch;
int lastX, lastY;
float acceleration = 1.0f;
bool inGround = false;

aws::Camera camera;

aws::Renderer ground;
aws::Renderer ground2;
aws::Renderer terrainMesh;

void mouse(GLFWwindow* window, double xpos, double ypos) {
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

		camera.SetCameraRotation(glm::radians(yaw), glm::radians(pitch), aws::Axis::xy);

		cameraFront = camera.GetCameraRotation(aws::CameraGetMode::Normalized);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Wnd::input() {
	if (GetKey(aws::Keys::W))
		playerPos -= aws::Vector(cameraFront.x, 0.0f, cameraFront.z) * aws::to_vec(speed * aws::time.GetDeltaTime());

	if (GetKey(aws::Keys::S))
		playerPos += aws::Vector(cameraFront.x, 0.0f, cameraFront.z) * aws::to_vec(speed * aws::time.GetDeltaTime());

	if (GetKey(aws::Keys::A))
		playerPos += cameraRight * aws::to_vec(speed * aws::time.GetDeltaTime());

	if (GetKey(aws::Keys::D))
		playerPos -= cameraRight * aws::to_vec(speed * aws::time.GetDeltaTime());

	if (GetKey(aws::Keys::SPACE) && inGround)
	{
		acceleration = -2.0f;
	}

	if (GetKey(aws::Keys::R) && aws::time.GetTime() > old + 2.0f)
	{
		ground.Terminate();

		ground.Init(aws::LoadShader("water.vert", aws::ShadType::vertex), aws::LoadShader("water.frag", aws::ShadType::fragment));
		ground.AddTexture("white.png");
		ground.SetTextureByID(0, 1);
		ground.SetColorByID(0, { 0.0f, 0.5f, 0.0f, 1.0f });

		ground.SetScale({ 10000.0f, 0.1f, 10000.0f });

		old = aws::time.GetTime();
	}

	speed = normal_speed;

	if (GetKey(aws::Keys::L_SHIFT))
	{
		speed = normal_speed * speed_mul;
	}

	cameraRight = camera.GetCameraRotation(aws::CameraGetMode::Crossed);

	camera.SetCameraPosition({ playerPos.x, playerPos.y, playerPos.z });
}

void framebuffer_call(GLFWwindow* window, int w, int h) {
	//Wnd::width = w;
	//Wnd::height = h;
	glViewport(0, 0, w, h);

	projection = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 10000.0f);
}

void physics() {
	playerPos.y -= aws::time.GetDeltaTime() * 20.0f * acceleration;

	inGround = aws::CheckAABBCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10000.0f, 0.1f, 10000.0f))
		|| aws::CheckAABBCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f))
		|| ground2.GetAABBTriggerByID(0, camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f))
		|| aws::CheckOBBBoxCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(glm::radians(45.0f), 0.0f, 0.0f))
		|| ch.AABBToMesh(camera.GetCameraPosition(), { 1.0f, 10.0f, 1.0f, 1.0f }, terrainMesh.GetMesh().vertices, { 0.0f, 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 10.0f, 10.0f });

	if (inGround)
	{
		playerPos.y += aws::time.GetDeltaTime() * 20.0f * fabs(acceleration);
	}

	if (acceleration < 2.5f)
	{
		acceleration += 5.0f * aws::time.GetDeltaTime();
	}

	w += 0.01f;
}

void Wnd::Start() {
	std::vector<float> wssd = { 65, 4, 32, 2, 47, 68, 6, 8, 23, 65, 31 };

	std::cout << aws::ClosestMatch(wssd.data(), wssd.size(), 50.0f) << '\n';

	vertical_synchronization = true;
	glfwSetFramebufferSizeCallback(GetWindow(), framebuffer_call);
	glfwSetCursorPosCallback(GetWindow(), mouse);
	framebuffer_call(GetWindow(), 800, 600);

	ground.Init();
	ground.SetRendererData(aws::cube);
	ground.SetColorByID(0, { 0.0f, 0.5f, 0.0f, 1.0f });
	ground.SetScale({ 10000.0f, 0.1f, 10000.0f });
	ground.SetUVMapByID(0, 2000.0f);
	ground.AddTexture("data/textures/grass.png");
	ground.SetTextureByID(0, 0);

	ground2.Init();
	ground2.SetRendererData(aws::cube);
	ground2.AddTexture("data/textures/awesomev2.png");

	ground2.SetScale({ 10.0f, 10.0f, 10.0f });
	ground2.SetPosition({ 0.0f, 20.0f, 0.0f });

	terrainMesh.Init();
	terrainMesh.SetRendererData(aws::LoadOBJModel("data/models/testTerrain.obj"));

	playerPos.y = 11.0f;
}

void Wnd::Update() {
	view = glm::lookAt(camera.GetCameraPosition().changeV3() + cameraFront.changeV3(), camera.GetCameraPosition().changeV3(), glm::vec3(0.0f, 1.0f, 0.0f));

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	
	ground.Render(projection, view);
	
	ground2.SetFloat3("cameraPos", { camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z });
	ground2.SetFloatMat4("view", 1, glm::value_ptr(view));
	ground2.SetFloatMat4("projection", 1, glm::value_ptr(projection));

	ground2.SetRotationByID(0, { glm::radians(w), glm::radians(w), 1.0f });

	w += aws::time.GetDeltaTime();

	if (w > 360.0f)
	{
		w = 0.0f;
	}

	ground2.Render(projection, view);

	terrainMesh.Render(projection, view);
	
	std::future<void> phys = std::async(physics);
}

void Wnd::LateUpdate() {
	input();
}

int main()
{
	Wnd window;

	window.CreateWindow("Window", 800, 600, nullptr);

	return 0;
}