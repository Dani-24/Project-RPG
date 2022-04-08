#include "App.h"
#include "Window.h"
#include "Camera.h"

#include "Defs.h"
#include "Log.h"

Camera::Camera(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("camera");
}

Camera::~Camera()
{}

bool Camera::Awake(pugi::xml_node& config) {

	LOG("Creating Camera");

	cam.w = app->win->screenSurface->w;
	cam.h = app->win->screenSurface->h;
	cam.x = 0;
	cam.y = 0;

	return true;
}

bool Camera::Start() {

	LOG("Camera starting . . .");

	camOffset.x = app->win->GetWidth() / 2;
	camOffset.y = app->win->GetHeight() / 2;

	return true;
}

bool Camera::Update(float dt) {

	if (target == nullptr) {
		LOG("NO TARGET");
		return true;
	}
	else {
		FollowTarget(dt);
	}

	return true;
}

bool Camera::CleanUp() {

	LOG("Freeing Camera");

	target = nullptr;

	return true;
}

void Camera::SetPos(iPoint position) {
	ReleaseTarget();
	cam.x = position.x;
	cam.y = position.y;
}

void Camera::FollowTarget(float dt) {

	// ========== X axis ==========
	if (cam.x != -target->position.x * app->win->GetScale() + app->win->GetWidth() / 2) {
		int distance = -cam.x + -target->position.x * app->win->GetScale() + app->win->GetWidth() / 2;
		if (distance > 0) {
			cam.x += speed * dt;
		}
		else {
			cam.x -= speed * dt;
		}
	}
	else {
		speed = 0.1f;
	}

	// ========== Y axis ==========
	if (cam.y != -target->position.y * app->win->GetScale() + app->win->GetWidth() / 2) {
		int distance = -cam.y + -target->position.y * app->win->GetScale() + app->win->GetWidth() / 2;
		if (distance > 0) {
			cam.y += speed * dt;
		}
		else {
			cam.y -= speed * dt;
		}
	}
	else {
		speed = 0.1f;
	}

	LOG("TArget X Y = %d %d CamerA X Y %d %d", target->position.x, target->position.y, cam.x, cam.y);
}

void Camera::OnTarget() {
	cam.x = -target->position.x * app->win->GetScale() + app->win->GetWidth() / 2;
	cam.y = -target->position.y * app->win->GetScale() + app->win->GetHeight() / 2;
}

bool Camera::SetTarget(Entity* target) {

	this->target = target;

	if (this->target != nullptr) {
		LOG("Camera Target Set");
	}
	else {
		LOG("Can't set camera Target");
		return false;
	}

	return true;
}

void Camera::ReleaseTarget() {
	target = nullptr;
	LOG("Camera Target Released");
}

// Load Game State
bool Camera::LoadState(pugi::xml_node& data)
{
	cam.x = data.child("camera").attribute("x").as_int();
	cam.y = data.child("camera").attribute("y").as_int();

	return true;
}

// Save Game State
bool Camera::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node camera = data.append_child("camera");

	camera.append_attribute("x") = cam.x;
	camera.append_attribute("y") = cam.y;

	return true;
}