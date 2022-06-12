#include "adder.h"
#include "multiplier.h"
#include <iostream>

int main() {
  std::cout << add(5.0f, 5.0f) << std::endl;
  std::cout << mult(5.0f, 5.0f) << std::endl;
  return 0;
}