#include "array.h"


int Array::size() const {
  return size;
}

T& Array::operator[](size_t index) {
  return (this->data)[index];
}

const T& Array::operator[](size_t index) const {
  return (this->data)[index];
}