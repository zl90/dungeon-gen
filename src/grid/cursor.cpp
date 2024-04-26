#include "../include/cursor.hpp"
#include <chrono>
#include <mutex>

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
  while (is_background_thread_running_) {
    auto now = TimeSinceEpochInMilliseconds();

    if (now - blink_start_time_ >= cursor_blink_interval_milliseconds_) {
      blink_state_ = !blink_state_;
      blink_start_time_ = now;
    }
  }
}

auto Cursor::RefreshBlinkTimer() -> void {
  auto now = TimeSinceEpochInMilliseconds();

  blink_state_ = true;
  blink_start_time_ = now;
}

Cursor::~Cursor() {
  is_background_thread_running_ = false;
  if (cursor_blink_background_thread_.has_value()) {
    cursor_blink_background_thread_->join();
  }
}