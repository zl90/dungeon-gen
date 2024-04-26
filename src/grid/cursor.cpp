#include "../include/cursor.hpp"
#include <chrono>

Cursor::Cursor() {
  cursor_blink_background_thread_.emplace(
      [&] { StartCursorBlinkBackgroundThread(); });
}

auto Cursor::GetBlinkState() -> bool { return blink_state_; }

auto Cursor::TimeSinceEpochInMilliseconds() -> uint64_t {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}

auto Cursor::StartCursorBlinkBackgroundThread() -> void {
  auto start = TimeSinceEpochInMilliseconds();

  while (is_background_thread_running_) {
    auto now = TimeSinceEpochInMilliseconds();

    if (now - start >= cursor_blink_interval_milliseconds_) {
      blink_state_ = !blink_state_;
      start = now;
    }
  }
}

Cursor::~Cursor() {
  is_background_thread_running_ = false;
  if (cursor_blink_background_thread_.has_value()) {
    cursor_blink_background_thread_->join();
  }
}