#include "event.h"

class KeyEvent : public Event {
private:
protected:
  int keyCode;
  KeyEvent(int keyCode)
    : keyCode(keyCode) {}  // protected constructor: subclass can invoke the constructor
                           // manually but class cannot be instantiated from outside
public:
  int GetCategory() const override;
};

class KeyPressedEvent : KeyEvent {
private:
  int repeatCount;
public:
  KeyPressedEvent(int keyCode, int repeatCount)
    : KeyEvent(keyCode), repeatCount(repeatCount) {}
  int GetRepeatCount() const;
  EventType GetType() const override;
  static EventType GetStaticType();
};

class KeyReleasedEvent : KeyEvent {
private:
public:
  KeyReleasedEvent(int keyCode)
    : KeyEvent(keyCode) {}
  EventType GetType() const override;
  static EventType GetStaticType();
};