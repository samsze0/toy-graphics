#include "eventDispatcher.h"

template<typename T>
bool EventDispatcher::Dispatch(std::function<bool (T &)> func) {
  if (this->event.GetType() == T::GetStaticType()) {
    // If the type matches, let func handles the event
    this->event.handled = func(this->event);
    return true;
  } else {
    return false;
  }
}