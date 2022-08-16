#include "event.h"

class WindowEvent : public Event {
private:
protected:
  WindowEvent() {}
public:
  int GetCategory() const override;
};

class WindowResizeEvent : WindowEvent {
private:
  float width, height;
public:
  WindowResizeEvent(float width, float height)
    : width(width), height(height) {}
  EventType GetType() const override;
  static EventType GetStaticType();
  float GetWidth() const;
  float GetHeight() const;
};

class WindowMovedEvent : WindowEvent {
private:
public:
  WindowMovedEvent() {}
  EventType GetType() const override;
  static EventType GetStaticType();
};

class WindowLostFocusEvent : WindowEvent {
private:
public:
  WindowLostFocusEvent() {}
  EventType GetType() const override;
  static EventType GetStaticType();
};

class WindowFocusEvent : WindowEvent {
private:
public:
  WindowFocusEvent() {}
  EventType GetType() const override;
  static EventType GetStaticType();
};

class WindowCloseEvent : WindowEvent {
private:
public:
  WindowCloseEvent() {}
  EventType GetType() const override;
  static EventType GetStaticType();
};