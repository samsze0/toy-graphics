#include "camera.h"
#include <iostream>


Camera::Camera(float speed)
  : speed(speed) {}

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(this->pos, this->target - this->pos, this->up);
}

void Camera::MoveLeft() {
  // Cross product: z x x = y
  // Move to left (hence the opposite of right vector)
  std::cout << "[Camera] Move left" << std::endl;
  this->pos -= glm::normalize(glm::cross(this->target - this->pos, this->up)) * this->speed;
}

void Camera::MoveRight() {
  std::cout << "[Camera] Move right" << std::endl;
  this->pos += glm::normalize(glm::cross(this->target - this->pos, this->up)) * this->speed;
}

void Camera::MoveForward() {
  std::cout << "[Camera] Move forward" << std::endl;
  this->pos += glm::normalize(this->target - this->pos) * this->speed;
}

void Camera::MoveBack() {
  std::cout << "[Camera] Move back" << std::endl;
  this->pos -= glm::normalize(this->target - this->pos) * this->speed;
}

void Camera::MoveUp() {
  std::cout << "[Camera] Move up" << std::endl;
  this->pos += this->up * this->speed;
}

void Camera::MoveDown() {
  std::cout << "[Camera] Move down" << std::endl;
  this->pos -= this->up * this->speed;
}