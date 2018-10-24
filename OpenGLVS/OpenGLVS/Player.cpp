#include "Player.h"
#include <iostream>

Player::Player(TexturedModel* texturedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: Entity(texturedModel, position, rotation, scale) {
	this->window = glfwGetCurrentContext();
	this->currentSpeed = 0;
	this->currentTurnSpeed = 0;
	this->upwardSpeed = 0;
	this->isGrounded = true;
	this->info = new Information();
}

void Player::movePlayer(double delta) 
{
	checkForInput();
	float distance = this->currentSpeed * delta;
	glm::vec3 rotation = this->getRotation();
	float dx = distance * glm::sin(glm::radians(rotation.y));
	float dz = distance * glm::cos(glm::radians(rotation.y));
	this->upwardSpeed += this->info->GRAVITY * delta;

	this->move(dx, this->upwardSpeed * delta, dz);
	this->rotate(0, this->currentTurnSpeed * delta, 0);

	if (this->getPosition().y < this->info->TERRAIN_HEIGHT)
	{
		this->isGrounded = true;
		this->upwardSpeed = 0;
		this->setPositionY(this->info->TERRAIN_HEIGHT);
	}
}

void Player::checkForInput() 
{
	if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
	{
		this->info->MOVE_SPEED = 40;
	}
	else
	{
		this->info->MOVE_SPEED = 20;
	}

	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS && this->isGrounded)
	{
		this->upwardSpeed = this->info->JUMP_FORCE;
		this->isGrounded = false;
	}

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		this->currentSpeed = this->info->MOVE_SPEED;
	} 
	else if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->currentSpeed = -this->info->MOVE_SPEED;
	} 
	else
	{
		this->currentSpeed = 0;
	}

	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->currentTurnSpeed = this->info->TURN_SPEED;
	}
	else if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->currentTurnSpeed = -this->info->TURN_SPEED;
	}
	else
	{
		this->currentTurnSpeed = 0;
	}
}