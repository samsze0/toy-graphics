#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
private:
  // For deriving camera position
  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);  // by default position at +ve z
  float speed = 0.003f;
  // glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);  // by default look at origin
  glm::vec3 lookAt;  // define by pitch and yaw
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

  // For deriving look target
  float yaw = -90.0f;  // yaw = 0 : look at +ve x, but we want to look at -ve z
  float pitch = 0.0f;
  float sensitivity = 0.1f;

  // Camera characteristics
  float fov = 60.0f;
  float far = 100.0f;

public:
  Camera();
  glm::mat4 GetViewMatrix() const;
  glm::mat4 GetProjectionMatrix(float aspect_ratio) const;
  void MoveLeft(float deltaTime);
  void MoveRight(float deltaTime);
  void MoveForward(float deltaTime);
  void MoveBack(float deltaTime);
  void MoveUp(float deltaTime);
  void MoveDown(float deltaTime);
  void Look(double x_offset, double y_offset);
  // float GetFOV() const;
  // void SetFOV(float fov);
  float& Speed();
  float& FOV();
};