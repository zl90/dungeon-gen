#pragma once

#include <mutex>
#include <optional>
#include <thread>

class Cursor {
public:
  Cursor();
  ~Cursor();

  int x = 0;
  int y = 0;

  auto GetBlinkState() -> bool;
  auto RefreshBlinkTimer() -> void;

private:
  /**
   * Blink state of the cursor.
   * true = ON.
   * false = OFF.
   */
  bool blink_state_ = true;
  int cursor_blink_interval_milliseconds_ = 300;
  uint64_t blink_start_time_ = 0;

  /** The background thread responsible for blinking the cursor on and off. */
  std::optional<std::thread> cursor_blink_background_thread_;
  /** Used to terminate the background thread upon destruction. */
  bool is_background_thread_running_ = true;

  auto StartCursorBlinkBackgroundThread() -> void;

  auto TimeSinceEpochInMilliseconds() -> uint64_t;
};