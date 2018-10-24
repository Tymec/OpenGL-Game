#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "Player.h"

class Camera
{
public:
	Camera(Player* player);
	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	float getRoll();
	float zoomOffsetY;
	float pitchOffsetY;
	float angleOffsetX;
	int mouseButtonPressed = -1;
	void setPosition(float dx, float dy, float dz);
	void setPitch(float pitch);
	void setYaw(float yaw);
	void setRoll(float roll);
	void move();
	void clear();
private:
	bool FIRST_PERSON = false;
	Player* player;
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;
	float distanceFromPlayer = 25;
	float angleAroundPlayer = 0;
	float calculateHorizontalDistance();
	float calculateVerticalDistance();
	void calculateCameraPosition(float horizontalDistance, float verticalDistance);
	void calculateZoom();
	void calculatePitch();
	void calculateAngle();
};

