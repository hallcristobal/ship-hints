#pragma once

#include "../../custom-message/CustomMessageManager.h"
#include <vector>

class HintText {
public:
  HintText() = default;
  HintText(CustomMessage clearText_,
           std::vector<CustomMessage> ambiguousText_ = {},
           std::vector<CustomMessage> obscureText_ = {})
      : clearText(std::move(clearText_)),
        ambiguousText(std::move(ambiguousText_)),
        obscureText(std::move(obscureText_)) {}

  const CustomMessage &getClearText() const { return clearText; };
  const std::vector<CustomMessage> &getAmbiguousText() const {
    return ambiguousText;
  }
  const std::vector<CustomMessage> &getObscureText() const {
    return obscureText;
  }

private:
  CustomMessage clearText;
  std::vector<CustomMessage> ambiguousText = {};
  std::vector<CustomMessage> obscureText = {};
};
