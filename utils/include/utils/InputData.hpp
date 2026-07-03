#pragma once

enum class KeyId {
  NO_INPUT,
  ARROW_UP,
  ARROW_DOWN,
};

struct InputData {
  KeyId key{'\0'};
  bool isMouse{false};
};
