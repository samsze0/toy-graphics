#include "event.h"

class AppEvent : public Event {
private:
protected:
  AppEvent() {}
public:
  int GetCategory() const override;
};

class AppRenderEvent : AppEvent {
private:
public:
  AppRenderEvent() {}
  static EventType GetStaticType();
  EventType GetType() const override;
};

class AppTickEvent : AppEvent {
private:
public:
  AppTickEvent() {}
  static EventType GetStaticType();
  EventType GetType() const override;
};

class AppUpdateEvent : AppEvent {
private:
public:
  AppUpdateEvent() {}
  static EventType GetStaticType();
  EventType GetType() const override;
};