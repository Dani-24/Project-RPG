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
		return true;
	}
	else {
		FollowTarget();
	}

	return true;
}

bool Camera::CleanUp() {

	LOG("Freeing Camera");

	target = nullptr;
	camLimited = false;

	return true;
}

void Camera::SetPos(iPoint position) {
	ReleaseTarget();
	cam.x = -position.x;
	cam.y = -position.y;
}

iPoint Camera::GetPos() {
	return { cam.x, cam.y };
}

void Camera::SetLimits(int x, int y, int w, int h) {
	limitX = x + app->win->GetWidth() / 2;
	limitY = y + app->win->GetHeight() / 2;
	limitW = w - app->win->GetWidth() / 2;
	limitH = h - app->win->GetHeight() / 2;
	camLimited = true;
	LOG("Camera limited to the area %d %d %d %d", x, y, w, h);
}

void Camera::FreeLimits() {
	limitX = limitY = limitW = limitH = 0;
	camLimited = false;
	LOG("Camera movement is no longer limited");
}

void Camera::FollowTarget() {

	// Variables for adjustments:
	int followDistance = 200;
	int slowCoefficient = 2;
	int speedDelay = 20;

	LOG("X= %d Y= %d ", target->position.x * app->win->GetScale() + app->win->GetWidth() / 2, target->position.y * app->win->GetScale() + app->win->GetHeight() / 2);

	// Simplify Target position + Camera limitation
	if (camLimited == false) {
		targetPos.x = -target->position.x * app->win->GetScale() + app->win->GetWidth() / 2;
		targetPos.y = -target->position.y * app->win->GetScale() + app->win->GetHeight() / 2;
	}
	else {
		// X
		if ((target->position.x * app->win->GetScale() + app->win->GetWidth() / 2) > limitX && (target->position.x * app->win->GetScale() + app->win->GetWidth() / 2) < limitW) {
			targetPos.x = -target->position.x * app->win->GetScale() + app->win->GetWidth() / 2;
		}
		// Y
		if ((target->position.y * app->win->GetScale() + app->win->GetHeight() / 2) > limitY && (target->position.y * app->win->GetScale() + app->win->GetHeight() / 2) < limitH) {
			targetPos.y = -target->position.y * app->win->GetScale() + app->win->GetHeight() / 2;
		}
	}

	// Distance between camera & target
	distance.x = abs(targetPos.x - cam.x);
	distance.y = abs(targetPos.y - cam.y);

	// =========== Camera MOVEMENT ===========

	// ========== X axis ==========

	if (distance.x > followDistance) {
		if (targetPos.x > cam.x) {
			cam.x += distance.x / (speedDelay / slowCoefficient);
		}
		else {
			if (targetPos.x < cam.x) {
				cam.x -= distance.x / (speedDelay / slowCoefficient);
			}
			else {
				cam.x = cam.x;
			}
		}
	}
	// Move Slower at closest distance
	else if (distance.x != 0) {
		if (targetPos.x > cam.x) {
			cam.x += distance.x / (speedDelay / 2);
		}
		else {
			if (targetPos.x < cam.x) {
				cam.x -= distance.x / (speedDelay / 2);
			}
			else {
				cam.x = cam.x;
			}
		}
	}

	// ========== Y axis ==========

	if (distance.y > followDistance) {
		if (targetPos.y > cam.y) {
			cam.y += distance.y / (speedDelay / slowCoefficient);
		}
		else {
			if (targetPos.y < cam.y) {
				cam.y -= distance.y / (speedDelay / slowCoefficient);
			}
			else {
				cam.y = cam.y;
			}
		}
	}
	// Move Slower at closest distance
	else if (distance.y != 0) {
		if (targetPos.y > cam.y) {
			cam.y += distance.y / (speedDelay / 2);
		}
		else {
			if (targetPos.y < cam.y) {
				cam.y -= distance.y / (speedDelay / 2);
			}
			else {
				cam.y = cam.y;
			}
		}
	}
}

void Camera::OnTarget() {
	cam.x = -target->position.x * app->win->GetScale() + app->win->GetWidth() / 2;
	cam.y = -target->position.y * app->win->GetScale() + app->win->GetHeight() / 2;
}

bool Camera::SetTarget(Entity* target) {

	this->target = target;

	if (this->target != nullptr) {
		LOG("Camera Target Set");
		OnTarget();
	}
	else {
		LOG("Can't set camera Target");
		return false;
	}

	return true;
}

void Camera::ReleaseTarget() {
	target = nullptr;
	FreeLimits();
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