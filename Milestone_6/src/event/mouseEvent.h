#include "event.h"

class MouseEvent : public Event {
private:
protected:
  MouseEvent() {}
public:
  int GetCategory() const override;
};

class MouseMovedEvent : public MouseEvent {
private:
  float x, y;
public:
  MouseMovedEvent(float x, float y)
    : MouseEvent(), x(x), y(y) {}
  EventType GetType() const override;
  static EventType GetStaticType();
  float GetX() const;
  float GetY() const;
};

class MouseScrolledEvent : public MouseEvent {
private:
  float xOffset, yOffset;
public:
  MouseScrolledEvent(float xOffset, float yOffset)  // For both vertical & horizontal scrolling
    : MouseEvent(), xOffset(xOffset), yOffset(yOffset) {}
  EventType GetType() const override;
  static EventType GetStaticType();
  float GetXOffset() const;
  float GetYOffset() const;
};

class MouseButtonEvent : MouseEvent {
private:
  int button;
protected:
  MouseButtonEvent(int button)
    : MouseEvent(), button(button) {}
public:
  int GetCategory() const override;
};

class MouseButtonPressedEvent : MouseButtonEvent {
private:
  int repeatCount;
public:
  MouseButtonPressedEvent(int button)
    : MouseButtonEvent(button) {}
  EventType GetType() const override;
  static EventType GetStaticType();
};

class MouseButtonReleasedEvent : MouseButtonEvent {
private:
public:
  MouseButtonReleasedEvent(int button)
    : MouseButtonEvent(button) {}
  EventType GetType() const override;
  static EventType GetStaticType();
};