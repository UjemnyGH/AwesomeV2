#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "e_Core.hpp"
#include "e_Renderer.hpp"
#include "e_Camera.hpp"
#include "e_Window.hpp"
#include "e_CollisionHandler.hpp"
#include "e_Raycast.hpp"
#include "e_Text.hpp"
#include "e_Math.hpp"

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

const float normal_speed = 80.0f;
const float speed_mul = 4.0f;

float speed = normal_speed;

float w = 0.0f;

float old = 0.0f;

glm::mat4 view = glm::mat4(1.0);
glm::mat4 projection = glm::mat4(1.0);
aws::math::Vector cameraFront = { 0.0f, 0.0f, -1.0f };
aws::math::Vector cameraRight;
aws::math::Vector playerPos = aws::math::Vector(0.0f, 0.0f, 0.0f);
aws::math::Vector playerVelocity = {0.0f, 0.0f, 0.0f};

float yaw, pitch;
int lastX, lastY;
float acceleration = 1.0f;
bool onGround = false;
bool inGround = false;

aws::Camera camera;

aws::math::Vector point;

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

		pitch = aws::math::clamp(-89.99f, 89.99f, pitch);

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
	if (GetKey(aws::Keys::W) && onGround) {
		playerVelocity.x -= cameraFront.x * speed * aws::time.GetDeltaTime();
		playerVelocity.z -= cameraFront.z * speed * aws::time.GetDeltaTime();
	}

	if (GetKey(aws::Keys::S) && onGround) {
		playerVelocity.x += cameraFront.x * speed * aws::time.GetDeltaTime();
		playerVelocity.z += cameraFront.z * speed * aws::time.GetDeltaTime();
	}

	if (GetKey(aws::Keys::A) && onGround) {
		playerVelocity.x += cameraRight.x * speed * aws::time.GetDeltaTime();
		playerVelocity.z += cameraRight.z * speed * aws::time.GetDeltaTime();
	}

	if (GetKey(aws::Keys::D) && onGround) {
		playerVelocity.x -= cameraRight.x * speed * aws::time.GetDeltaTime();
		playerVelocity.z -= cameraRight.z * speed * aws::time.GetDeltaTime();
	}

	if (GetKey(aws::Keys::SPACE) && onGround && !inGround)
	{
		acceleration = -2.0f;
	}

	speed = normal_speed;

	if (GetKey(aws::Keys::L_SHIFT) && !inGround)
	{
		speed = normal_speed * speed_mul;
	}

	playerPos += playerVelocity;

	cameraRight = camera.GetCameraRotation(aws::CameraGetMode::Crossed);

	camera.SetCameraPosition({ playerPos.x, playerPos.y, playerPos.z });
}

void framebuffer_call(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);

	projection = glm::perspectiveFov(70.0f, (float)w, (float)h, 0.001f, 50000.0f);
}

void physics() {
	playerVelocity.x = aws::math::clamp(-50.0f, 50.0f, playerVelocity.x);
	playerVelocity.y = aws::math::clamp(-50.0f, 50.0f, playerVelocity.y);
	playerVelocity.z = aws::math::clamp(-50.0f, 50.0f, playerVelocity.z);

	playerPos.y -= aws::time.GetDeltaTime() * 20.0f * acceleration;

	onGround = false;

	onGround = aws::physics::CheckAABBCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10000.0f, 0.1f, 10000.0f)) ||
		ground3.GetAABBTriggerByID(0, camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f));
		//|| ground2.GetAABBTriggerByID(0, camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f));
		//|| aws::CheckOBBBoxCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));
		//|| ch.AABBToMesh(camera.GetCameraPosition(), { 1.0f, 10.0f, 1.0f, 1.0f }, terrainMesh.GetMesh().vertices, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	inGround = aws::physics::CheckAABBCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f) * glm::vec3(1.0f, 0.9f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10000.0f, 0.1f, 10000.0f)) ||
		ground3.GetAABBTriggerByID(0, camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f) * glm::vec3(1.0f, 0.9f, 1.0f));
		//|| ground2.GetAABBTriggerByID(0, camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f) * glm::vec3(1.0f, 0.9f, 1.0f));
		//|| aws::CheckOBBBoxCollision(camera.GetCameraPositionV3(), glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(glm::radians(45.0f), 0.0f, 0.0f));
		//|| ch.AABBToMesh(camera.GetCameraPosition(), { 1.0f, 10.0f, 1.0f, 1.0f }, terrainMesh.GetMesh().vertices, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	if (onGround)
	{
		playerPos.y += aws::time.GetDeltaTime() * 20.0f * fabs(acceleration);
		playerVelocity -= playerVelocity * (aws::math::to_vec(aws::time.GetDeltaTime()) * 0.01f);
	}

	if (inGround)
	{
		playerVelocity = aws::math::Vector(cameraFront.x * speed * aws::time.GetDeltaTime(), 0.0f, cameraFront.z * speed * aws::time.GetDeltaTime());
	}

	if (acceleration < 2.5f)
	{
		acceleration += 5.0f * aws::time.GetDeltaTime();
	}

	point = rc.GetPoint(playerPos, camera.GetCameraRotation(aws::CameraGetMode::Normalized) + playerPos, aws::cube);

	w += 0.001f;
}

void Wnd::Start() {
	__debug_file = fopen("Debug.txt", "w+");
	aws::GlobalLight = { 1.0f, 0.6f, 1.0f, 1.0f };
	vertical_synchronization = true;
	glfwSetFramebufferSizeCallback(GetWindow(), framebuffer_call);
	glfwSetCursorPosCallback(GetWindow(), mouse);
	framebuffer_call(GetWindow(), 800, 600);

	point1.Init(aws::LoadShader("light.vert", aws::ShadType::vertex), aws::LoadShader("light.frag", aws::ShadType::fragment));
	point1.SetRendererData(aws::cube);
	point1.SetScale({ 0.1f, 0.1f, 0.1f });

	ground2.Init(aws::vs, aws::fs);
	ground2.SetRendererData(aws::LoadOBJModel("data/models/skybox_cube.obj"));
	ground2.AddTexture("data/textures/skybox_texture2.png");

	ground2.SetScaleByID(0, { 10000.0f, 10000.0f, 10000.0f });
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

	ground2.SetPosition(playerPos);
	
	w += aws::time.GetDeltaTime() * 100;

	if (w > 360.0f)
	{
		w = 0.0f;
	}

	ground2.Render(projection, view);
	ground3.Render(projection, view);
	point1.Render(projection, view);

	terrainMesh.Render(projection, view);

	printf("FPS: %1.f\n", 1.0f / aws::time.GetDeltaTime());
	
	std::future<void> phys = std::async(physics);
}

void Wnd::LateUpdate() {
	//std::future<void> test_th = std::async(tests);

	input();
}

int main()
{
	Wnd window;

	window.CreateWindow("Window", 800, 600, nullptr);

	fclose(__debug_file);

	return 0;
}