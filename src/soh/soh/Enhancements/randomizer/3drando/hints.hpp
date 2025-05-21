#pragma once

#include "../../custom-message/CustomMessageManager.h"
#include <vector>

class HintText {
public:
  HintText() = default;
  HintText(CustomMessage clearText_, std::vector<CustomMessage> ambiguousText_ = {},
           std::vector<CustomMessage> obscureText_ = {})
      : clearText(std::move(clearText_)),
        ambiguousText(std::move(ambiguousText_)),
        obscureText(std::move(obscureText_)) {}

private:
  CustomMessage clearText;
  std::vector<CustomMessage> ambiguousText = {};
  std::vector<CustomMessage> obscureText = {};
};
