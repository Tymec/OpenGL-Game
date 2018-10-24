#include "Camera.h"

Camera::Camera(Player* player)
{
	this->FIRST_PERSON = FIRST_PERSON;
	this->player = player;
	this->position = glm::vec3(0, 0, 0);
	this->pitch = 20;
	this->yaw = 0;
	this->roll = 0;
}

void Camera::move() 
{
	if (FIRST_PERSON) 
	{
		this->position = this->player->getPosition();
		this->yaw = -this->player->getRotation().y + 180;
		this->position.y += 5;
	}
	else
	{
		calculateZoom();
		calculatePitch();
		calculateAngle();
		float horizontalDistance = calculateHorizontalDistance();
		float verticalDistance = calculateVerticalDistance();
		calculateCameraPosition(horizontalDistance, verticalDistance);
	}
}

void Camera::clear() 
{
	this->zoomOffsetY = 0;
	this->pitchOffsetY = 0;
	this->angleOffsetX = 0;
}

void Camera::calculateCameraPosition(float horizontalDistance, float verticalDistance)
{
	float theta = this->player->getRotation().y + this->angleAroundPlayer;
	float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
	float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));
	this->position.x = this->player->getPosition().x - offsetX;
	float playerCenter = this->player->getTexturedModel()->getModel()->getHeight() * this->player->getScale().y;
	this->position.y = this->player->getPosition().y + verticalDistance + playerCenter;
	this->position.z = this->player->getPosition().z - offsetZ;
	this->yaw = 180 - theta;
}

float Camera::calculateHorizontalDistance() 
{
	return this->distanceFromPlayer * glm::cos(glm::radians(this->pitch));
}

float Camera::calculateVerticalDistance()
{
	return this->distanceFromPlayer * glm::sin(glm::radians(this->pitch));
}

void Camera::calculateZoom()
{
	if (this->distanceFromPlayer < 5.0f && this->zoomOffsetY > 0) 
	{
		this->zoomOffsetY = 0;
	}
	else if (this->distanceFromPlayer > 50.0f && this->zoomOffsetY < 0) 
	{
		this->zoomOffsetY = 0;
	}
	float zoomLevel = this->zoomOffsetY * 0.5f;
	this->distanceFromPlayer -= zoomLevel;
}

void Camera::calculatePitch()
{
	if (glm::radians(this->pitch) > 0.5f && this->pitchOffsetY < 0)
	{
		this->pitchOffsetY = 0;
	}
	else if(glm::radians(this->pitch) < 0 && this->pitchOffsetY > 0)
	{
		this->pitchOffsetY = 0;
	}
	if (this->mouseButtonPressed == 1) 
	{
		float pitchChange = this->pitchOffsetY * 0.1f;
		this->pitch -= pitchChange;
	}
}

void Camera::calculateAngle() 
{
	if (this->mouseButtonPressed == 0)
	{
		float angleChange = this->angleOffsetX * 0.1f;
		this->angleAroundPlayer -= angleChange;
	}
}

glm::vec3 Camera::getPosition()
{
	return this->position;
}

float Camera::getPitch()
{
	return this->pitch;
}

float Camera::getYaw()
{
	return this->yaw;
}

float Camera::getRoll()
{
	return this->roll;
}

void Camera::setPosition(float dx, float dy, float dz)
{
	this->position.x = dx;
	this->position.y = dy;
	this->position.z = dz;
}

void Camera::setPitch(float pitch)
{
	this->pitch = pitch;
}

void Camera::setYaw(float yaw)
{
	this->yaw = yaw;
}

void Camera::setRoll(float roll)
{
	this->roll = roll;
}