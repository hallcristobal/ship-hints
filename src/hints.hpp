#pragma once

#include "text.hpp"

#include "./message_data_textbox_types.h"
#include "./CustomMessageManager.h"

#include <string>
#include <vector>

class HintText {
public:
  HintText() = default;
  HintText(CustomMessage clearText_,
           std::vector<CustomMessage> ambiguousText_ = {},
           std::vector<CustomMessage> obscureText_ = {});
  const CustomMessage &GetClear() const;
  const CustomMessage &GetObscure() const;
  const CustomMessage &GetObscure(uint8_t selection) const;
  const CustomMessage &GetAmbiguous() const;
  const CustomMessage &GetAmbiguous(uint8_t selection) const;
  uint8_t GetAmbiguousSize() const;
  uint8_t GetObscureSize() const;
  const CustomMessage &GetHintMessage(uint8_t selection = 0) const;
  const CustomMessage GetMessageCopy() const;
  bool operator==(const HintText &right) const;
  bool operator!=(const HintText &right) const;

private:
  CustomMessage clearText;
  std::vector<CustomMessage> ambiguousText = {};
  std::vector<CustomMessage> obscureText = {};
};
