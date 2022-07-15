#include "camera.h"


static glm::vec3 CalculateLookTarget(float yaw, float pitch) {
  glm::vec3 direction;
  // yaw: angle of rotation by y-axis (horizontal)
  // pitch: angle of rotation by x-axis (vertical)
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  return glm::normalize(direction);
}

Camera::Camera() {
  this->lookAt = CalculateLookTarget(this->yaw, this->pitch);
}

glm::mat4 Camera::GetViewMatrix() const {
  // return glm::lookAt(this->pos, this->target, this->up);
  return glm::lookAt(this->pos, this->pos + this->lookAt, this->up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspect_ratio) const {
  // Orthogonal view volume: centered at 0 in world space, 4:3 aspect ratio
  // glm::ortho(L, R, T, B, Near, Far)
  // glm::mat4 projMat = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
  // glm::perspective(fov, aspect ratio, near, far)
  return glm::perspective(glm::radians(this->fov), aspect_ratio, 0.1f, this->far);
}

void Camera::MoveLeft(float deltaTime) {
  // Cross product: z * x = y
  // Move to left (hence the opposite of right vector)
  std::cout << "[Camera] Move left" << std::endl;
  // this->pos -= glm::normalize(glm::cross(this->target - this->pos, this->up)) * this->speed * deltaTime;
  this->pos -= glm::normalize(glm::cross(this->lookAt, this->up)) * this->speed * deltaTime;
}

void Camera::MoveRight(float deltaTime) {
  std::cout << "[Camera] Move right" << std::endl;
  // this->pos += glm::normalize(glm::cross(this->target - this->pos, this->up)) * this->speed * deltaTime;
  this->pos += glm::normalize(glm::cross(this->lookAt, this->up)) * this->speed * deltaTime;
}

void Camera::MoveForward(float deltaTime) {
  std::cout << "[Camera] Move forward" << std::endl;
  // this->pos += glm::normalize(this->target - this->pos) * this->speed * deltaTime;
  this->pos += glm::normalize(this->lookAt) * this->speed * deltaTime;
}

void Camera::MoveBack(float deltaTime) {
  std::cout << "[Camera] Move back" << std::endl;
  // this->pos -= glm::normalize(this->target - this->pos) * this->speed * deltaTime;
  this->pos -= glm::normalize(this->lookAt) * this->speed * deltaTime;
}

void Camera::MoveUp(float deltaTime) {
  std::cout << "[Camera] Move up" << std::endl;
  this->pos += this->up * this->speed * deltaTime;
}

void Camera::MoveDown(float deltaTime) {
  std::cout << "[Camera] Move down" << std::endl;
  this->pos -= this->up * this->speed * deltaTime;
}

void Camera::Look(double x_offset, double y_offset) {
  std::cout << "[Camera] Look x_offset " << x_offset << " y_offset " << y_offset << std::endl;

  this->yaw += x_offset * this->sensitivity;

  this->pitch += y_offset * this->sensitivity;
  // Prevent "lookup flip"
  if(this->pitch > 89.0f)  // Can be simplified using min and max
    this->pitch = 89.0f;
  if(this->pitch < -89.0f)
    this->pitch = -89.0f;

  this->lookAt = CalculateLookTarget(this->yaw, this->pitch);
}

// float Camera::GetFOV() const {
//   return this->fov;
// }

// void Camera::SetFOV(float fov) {
//   this->fov = fov;
// }

float& Camera::Speed() {
  return this->speed;
}

float& Camera::FOV() {
  return this->fov;
}