#include "windowEvent.h"

int WindowEvent::GetCategory() const {
  return EventCategoryWindow;
}

EventType WindowResizeEvent::GetType() const {
  return EventType::WindowResize;
}

EventType WindowMovedEvent::GetType() const {
  return EventType::WindowMoved;
}

EventType WindowCloseEvent::GetType() const {
  return EventType::WindowClose;
}

EventType WindowFocusEvent::GetType() const {
  return EventType::WindowFocus;
}

EventType WindowLostFocusEvent::GetType() const {
  return EventType::WindowLostFocus;
}

EventType WindowResizeEvent::GetStaticType() {
  return EventType::WindowResize;
}

EventType WindowMovedEvent::GetStaticType() {
  return EventType::WindowMoved;
}

EventType WindowCloseEvent::GetStaticType() {
  return EventType::WindowClose;
}

EventType WindowFocusEvent::GetStaticType() {
  return EventType::WindowFocus;
}

EventType WindowLostFocusEvent::GetStaticType() {
  return EventType::WindowLostFocus;
}

float WindowResizeEvent::GetWidth() const {
  return this->width;
}

float WindowResizeEvent::GetHeight() const {
  return this->height;
}