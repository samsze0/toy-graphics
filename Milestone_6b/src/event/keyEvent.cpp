#include "keyEvent.h"

int KeyEvent::GetCategory() const {
  return EventCategoryInput | EventCategoryKeyboard;
}

EventType KeyPressedEvent::GetType() const {
  return EventType::KeyPressed;
}

EventType KeyReleasedEvent::GetType() const {
  return EventType::KeyReleased;
}

EventType KeyPressedEvent::GetStaticType() {
  return EventType::KeyPressed;
}

EventType KeyReleasedEvent::GetStaticType() {
  return EventType::KeyReleased;
}