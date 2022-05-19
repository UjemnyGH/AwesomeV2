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
#include "Raycast.hpp"
#include "Text.hpp"

aws::CollisionHandler ch;
aws::Raycast rc;

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

aws::Vector point;

aws::Renderer ground2;
aws::Renderer ground3;
aws::Renderer point1;
aws::Renderer terrainMesh;
aws::Text text;

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

		pitch = aws::clamp(-89.99f, 89.99f, pitch);

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

	projection = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 100000.0f);
}

void physics() {
	playerPos.y -= aws::time.GetDeltaTime() * 20.0f * acceleration;

	inGround = aws::CheckAABBCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10000.0f, 0.1f, 10000.0f))
		|| aws::CheckAABBCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f))
		|| ground2.GetAABBTriggerByID(0, camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f));
		//|| aws::CheckOBBBoxCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));
		//|| ch.AABBToMesh(camera.GetCameraPosition(), { 1.0f, 10.0f, 1.0f, 1.0f }, terrainMesh.GetMesh().vertices, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	if (inGround)
	{
		playerPos.y += aws::time.GetDeltaTime() * 20.0f * fabs(acceleration);
	}

	if (acceleration < 2.5f)
	{
		acceleration += 5.0f * aws::time.GetDeltaTime();
	}

	point = rc.GetPoint(playerPos, camera.GetCameraRotation(aws::CameraGetMode::Normalized) + playerPos, aws::cube);

	w += 0.001f;
}

aws::RenderedData s = aws::LoadOBJModel("data/models/testTerrain.obj");

void Wnd::Start() {
	aws::GlobalLight = { 1.0f, 0.6f, 1.0f, 1.0f };
	vertical_synchronization = false;
	glfwSetFramebufferSizeCallback(GetWindow(), framebuffer_call);
	glfwSetCursorPosCallback(GetWindow(), mouse);
	framebuffer_call(GetWindow(), 800, 600);

	point1.Init(aws::LoadShader("light.vert", aws::ShadType::vertex), aws::LoadShader("light.frag", aws::ShadType::fragment));
	point1.SetRendererData(aws::cube);
	point1.SetScale({ 0.1f, 0.1f, 0.1f });

	text.Init();
	text.SetText("QWERTYUIOPASDFGHJKLZXCVBNM");

	ground2.Init(aws::LoadShader("light.vert", aws::ShadType::vertex), aws::LoadShader("light.frag", aws::ShadType::fragment));
	ground2.SetRendererData(aws::cube);
	ground2.AddTexture("white.png");

	ground2.SetScale({ 10.0f, 10.0f, 10.0f });
	ground2.SetPosition({ 0.0f, 20.0f, 0.0f });

	ground3.Init(aws::LoadShader("light.vert", aws::ShadType::vertex), aws::LoadShader("light.frag", aws::ShadType::fragment));
	ground3.SetRendererData(aws::cube);
	ground3.SetPosition({ 50.0f, 15.0f, 0.0f });
	ground3.SetScale({ 10.0f, 10.0f, 10.0f });

	terrainMesh.Init(aws::LoadShader("light.vert", aws::ShadType::vertex), aws::LoadShader("light.frag", aws::ShadType::fragment));
	terrainMesh.SetRendererData(aws::LoadOBJModel("data/models/testTerrain.obj"));
	terrainMesh.AddTexture("data/textures/grass.png");
	terrainMesh.SetColorByID(0, { 0.0f, 0.75f, 0.0f, 1.0f });
	terrainMesh.SetUVMapByID(0, 100.0f);

	playerPos.y = 11.0f;
}

void Wnd::Update() {
	view = glm::lookAt(camera.GetCameraPosition().changeV3() + cameraFront.changeV3(), camera.GetCameraPosition().changeV3(), glm::vec3(0.0f, 1.0f, 0.0f));

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	
	ground2.SetFloat3("cameraPos", camera.GetCameraPosition());
	ground2.SetFloatMat4("view", 1, glm::value_ptr(view));
	ground2.SetFloatMat4("projection", 1, glm::value_ptr(projection));

	ground2.SetRotationByID(0, { glm::radians(w), glm::radians(w), 1.0f });

	w += aws::time.GetDeltaTime();

	if (w > 360.0f)
	{
		w = 0.0f;
	}

	ground2.Render(projection, view);
	ground3.Render(projection, view);
	point1.Render(projection, view);

	terrainMesh.Render(projection, view);

	text.Render();
	
	std::future<void> phys = std::async(physics);
}

void tests()
{
	float x = aws::ClosestMatch(s.vertices, playerPos.x);
	float y = aws::ClosestMatch(s.vertices, playerPos.y);
	float z = aws::ClosestMatch(s.vertices, playerPos.z);

	size_t xi = aws::basicSearch(0, s.vertices.size() - 1, s.vertices, x);
	size_t yi = aws::basicSearch(0, s.vertices.size() - 1, s.vertices, y);
	size_t zi = aws::basicSearch(0, s.vertices.size() - 1, s.vertices, z);

	std::cout << "DELTA: " << 1.0f / aws::time.GetDeltaTime() << " X: " << x << ' ' << xi << " Y: " << y << ' ' << yi << " Z: " << z << ' ' << zi << " PX: " << playerPos.x << " PY: " << playerPos.y << " PZ: " << playerPos.z << '\n';
}

void Wnd::LateUpdate() {
	//std::future<void> test_th = std::async(tests);

	input();
}

int main()
{
	Wnd window;

	window.CreateWindow("Window", 800, 600, nullptr);

	return 0;
}