#pragma once


// To lookup: iterator, range-based for loop
template<typename T, size_t size>
class Array {
private:
  T data[size];  // stack allocation. Invoking the default constructor of array
public:
  constexpr size_t size() const;  // const method: promise not to modify class fields
                                        // constexpr: function can be evaluated at compile time
  T& operator[](size_t index);    // operator overloading. Return ref to avoid copying & allow assignment
  const T& operator[](size_t index) const;  // invoke this version (and return const ref) if the class obj is const
};