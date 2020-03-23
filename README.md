## Coroutine as Error Handling

Either monad by coroutine introduced in C++20 based on [tl::expected](https://github.com/TartanLlama/expected) and [coroutine_monad](https://github.com/toby-allsopp/coroutine_monad)



Example:

```cpp
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
  std::cout << sqrt_of_quotient(32, 2) << std::endl;   // Result: 4
  std::cout << sqrt_of_quotient(10, -1) << std::endl;  // Error: Radicand in sqrtm < 0
  std::cout << sqrt_of_quotient(-8, -2) << std::endl;  // Error: Dividend in dividem is 0
  return 0;
}
```



Reference: 

https://github.com/toby-allsopp/coroutine_monad

https://github.com/TartanLlama/expected