#include "appEvent.h"

int AppEvent::GetCategory() const {
  return EventCategoryApplication;
}

EventType AppUpdateEvent::GetType() const {
  return EventType::AppUpdate;
}

EventType AppTickEvent::GetType() const {
  return EventType::AppTick;
}

EventType AppRenderEvent::GetType() const {
  return EventType::AppRender;
}

EventType AppUpdateEvent::GetStaticType() {
  return EventType::AppUpdate;
}

EventType AppTickEvent::GetStaticType() {
  return EventType::AppTick;
}

EventType AppRenderEvent::GetStaticType() {
  return EventType::AppRender;
}