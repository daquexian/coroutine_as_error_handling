#ifndef EITHER_H
#define EITHER_H

// Make std::optional behave like the Maybe monad when used in a coroutine.

#include "return_object_holder.h"

#include <experimental/coroutine>
#include "expected.hpp"

template <typename T, typename E>
struct either_promise {
  return_object_holder<tl::expected<T, E>>* data;

  auto get_return_object() { return make_return_object_holder(data); }
  auto initial_suspend() { return std::experimental::suspend_never{}; }
  auto final_suspend() { return std::experimental::suspend_never{}; }

  void return_value(T x) { data->emplace(std::move(x)); }
  void unhandled_exception() {}
};

// This makes std::optional<T> useable as a coroutine return type. Strictly, this
// specilaization should depend on a user-defined type, otherwise this is undefined
// behaviour. As this is purely for demonstration purposes, let's live dangerously.
namespace std::experimental {
  template <typename T, typename E, typename... Args>
  struct coroutine_traits<tl::expected<T, E>, Args...> {
    using promise_type = ::either_promise<T, E>;
  };
}  // namespace std::experimental

template <typename T, typename E>
struct either_awaitable {
  tl::expected<T, E> o;
  auto await_ready() { return o.has_value(); }
  auto await_resume() { return *o; }

  template <typename U, typename V>
  void await_suspend(std::experimental::coroutine_handle<either_promise<U, V>> h) {
    h.promise().data->emplace(o);
    h.destroy();
  }
};

template <typename T, typename E>
auto operator co_await(tl::expected<T, E> o) {
  return either_awaitable<T, E>{std::move(o)};
}

#endif  // EITHER_H

