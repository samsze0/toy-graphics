#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
private:
  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  float speed;
public:
  Camera(float speed);
  glm::mat4 GetViewMatrix() const;
  void MoveLeft();
  void MoveRight();
  void MoveForward();
  void MoveBack();
  void MoveUp();
  void MoveDown();
};