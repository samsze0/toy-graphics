#include "event.h"

bool Event::IsInCategory(EventCategory category) const {
  return this->GetCategory() & category;
}