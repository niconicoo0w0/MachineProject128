#include "color.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  const int kMax= 255;
  int min = 0;
  if (red_ > kMax || red_ < min || green_ > kMax || green_ < min || blue_ > kMax || blue_ < min) {
    throw std::runtime_error("invalid color");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}