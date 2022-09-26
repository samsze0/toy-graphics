#pragma once

#define BIT(x) 1 << (x-1)

enum class EventType {  // enum class is more type-safe & no implicit conversions
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  AppTick,
  AppUpdate,
  AppRender,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

enum EventCategory {  // impossible to specify all possible combinations of event categories
                      // therefore use plain enum instead
  None = 0,
  EventCategoryApplication = BIT(1),
  EventCategoryInput = BIT(2),
  EventCategoryKeyboard = BIT(3),
  EventCategoryMouse = BIT(4),
  EventCategoryMouseButton = BIT(5),
  EventCategoryWindow = BIT(6),
};

class Event {
private:
protected:
public:
  bool handled = false;
  bool IsInCategory(EventCategory category) const;
  virtual int GetCategory() const;
  virtual EventType GetType() const;
  static EventType GetStaticType();
};