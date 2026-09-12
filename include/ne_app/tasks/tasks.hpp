// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <atomic>
#include <boost/asio/io_context.hpp>
#include <boost/throw_exception.hpp>
#include <functional>
#include <ne_app/core/store.hpp>
#include <stdexcept>
#include <utility>

namespace ne_app::tasks {

struct task_tag final {
  std::atomic_flag tf_{ATOMIC_FLAG_INIT};
  task_tag() = default;
  ~task_tag() = default;
};

template <typename Args, typename... Args2>
void run(const std::function<Args>& fn, task_tag& t, Args2... a) {
  while (!t.tf_.test_and_set(std::memory_order_acquire));

  try {
    fn(t.tf_, a...);
  } catch (...) {
    t.tf_.clear(std::memory_order_release);
    boost::throw_exception(std::runtime_error("task_error"));
  }

  t.tf_.clear(std::memory_order_release);
}

}  // namespace ne_app::tasks
