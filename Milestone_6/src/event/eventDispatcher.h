#include "event.h"
#include "../pch.h"

class EventDispatcher {
private:
  Event& event;
public:
  EventDispatcher(Event& event)
    : event(event) {}
  // Dispatch a function that handles the event
  template<typename T>
  bool Dispatch (std::function<bool(T&)> func);  // A function that takes T& and returns bool
};