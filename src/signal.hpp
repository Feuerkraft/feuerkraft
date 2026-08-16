// Feuerkraft - A Tank Battle Game
// Copyright (C) 2026 Ingo Ruhnke <grumbel@gmail.com>
//
// Minimal signal/slot replacement for ClanLib CL_Signal / CL_Slot.
// Supports the connect(obj, &Class::method) pattern used in the codebase.

#ifndef HEADER_SIGNAL_HXX
#define HEADER_SIGNAL_HXX

#include <functional>
#include <vector>
#include <memory>

/** Opaque connection handle (replaces CL_Slot). Keeping the connection
 *  alive is optional; signals hold their own copies of the callbacks. */
class Slot
{
public:
  Slot() {}
};

template<typename... Args>
class Signal
{
public:
  using Callback = std::function<void(Args...)>;

  Signal() {}

  /** Connect a free function or lambda. */
  Slot connect(Callback cb)
  {
    callbacks.push_back(std::move(cb));
    return Slot();
  }

  /** Connect a member function: sig.connect(obj, &Class::method) */
  template<typename T>
  Slot connect(T* obj, void (T::*method)(Args...))
  {
    callbacks.push_back([obj, method](Args... args) {
      (obj->*method)(args...);
    });
    return Slot();
  }

  /** Connect a const member function. */
  template<typename T>
  Slot connect(T* obj, void (T::*method)(Args...) const)
  {
    callbacks.push_back([obj, method](Args... args) {
      (obj->*method)(args...);
    });
    return Slot();
  }

  void operator()(Args... args) const
  {
    for (const auto& cb : callbacks)
      cb(args...);
  }

  void clear() { callbacks.clear(); }

private:
  std::vector<Callback> callbacks;
};

// Aliases matching ClanLib naming used in the tree
using Signal_v0 = Signal<>;
using Signal_v1_float = Signal<float>;

#endif

/* EOF */
