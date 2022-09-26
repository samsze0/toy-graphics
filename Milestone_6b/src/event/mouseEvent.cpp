#include "mouseEvent.h"

int MouseEvent::GetCategory() const {
  return EventCategoryMouse | EventCategoryInput;
}

int MouseButtonEvent::GetCategory() const {
  return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton;
}

EventType MouseMovedEvent::GetType() const {
  return EventType::MouseMoved;
}

EventType MouseMovedEvent::GetStaticType() {
  return EventType::MouseMoved;
}

float MouseMovedEvent::GetX() const {
  return this->x;
}

float MouseMovedEvent::GetY() const {
  return this->y;
}

EventType MouseScrolledEvent::GetType() const {
  return EventType::MouseScrolled;
}

EventType MouseScrolledEvent::GetStaticType() {
  return EventType::MouseScrolled;
}

float MouseScrolledEvent::GetXOffset() const {
  return this->xOffset;
}

float MouseScrolledEvent::GetYOffset() const {
  return this->yOffset;
}

EventType MouseButtonPressedEvent::GetType() const {
  return EventType::MouseButtonPressed;
}

EventType MouseButtonReleasedEvent::GetType() const {
  return EventType::MouseButtonReleased;
}

EventType MouseButtonPressedEvent::GetStaticType() {
  return EventType::MouseButtonPressed;
}

EventType MouseButtonReleasedEvent::GetStaticType() {
  return EventType::MouseButtonReleased;
}