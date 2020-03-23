#include "either.h"

#include <iostream>
#include <string>

using std::string;
using tl::expected;
using tl::make_unexpected;

expected<float, string> dividem(float a, float b) {
  if (b == 0) {
    return make_unexpected("Dividend in dividem is 0");
  }
  return a / b;
}

expected<float, string> sqrtm(float a) {
  if (a < 0) {
    return make_unexpected("Radicand in sqrtm < 0");
  }
  return sqrt(a);
}

expected<float, string> sqrt_of_quotient(float a, float b) {
  float c = trym dividem(a, b);
  float d = trym sqrtm(c);
  retm d;
}

int main() {
  std::cout << sqrt_of_quotient(1, 0) << std::endl;
  std::cout << sqrt_of_quotient(9, 1) << std::endl;
  std::cout << sqrt_of_quotient(32, 2) << std::endl;
  std::cout << sqrt_of_quotient(10, -1) << std::endl;
  std::cout << sqrt_of_quotient(-8, -2) << std::endl;
  return 0;
}
