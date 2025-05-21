#pragma once
#include "../randomizer/3drando/text.hpp"
#include "message_data_textbox_types.h"
#include <cstdint>
#include <string>
#include <vector>

typedef uint32_t ItemID;

#define TODO_TRANSLATE "TranslateThis"

#define QM_WHITE "\x00"s
#define QM_RED "\x41"
#define QM_GREEN "\x42"
#define QM_BLUE "\x43"
#define QM_LBLUE "\x44"
#define QM_PINK "\x45"
#define QM_YELLOW "\x46"
#define QM_BLACK "\x47"

#define HS_HORSE_ARCHERY "\x00"s // HS_HBA is an enum already

typedef enum {
  MF_FORMATTED,
  MF_CLEAN,
  MF_RAW,
  MF_AUTO_FORMAT,
  MF_ENCODE,
} MessageFormat;

class CustomMessage {
public:
  CustomMessage() = default;
  CustomMessage(std::string english_, std::string german_, std::string french_,
                TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
  CustomMessage(std::string english_, std::string german_, std::string french_,
                std::vector<std::string> colors_,
                std::vector<bool> capital_ = {},
                TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
  CustomMessage(std::string english_, TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
  CustomMessage(std::string english_, std::vector<std::string> colors_,
                std::vector<bool> capital_ = {},
                TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
  CustomMessage(Text text, TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);

  const std::string GetEnglish(MessageFormat format = MF_FORMATTED) const;
  const std::string GetFrench(MessageFormat format = MF_FORMATTED) const;
  const std::string GetGerman(MessageFormat format = MF_FORMATTED) const;
  const std::string GetForLanguage(uint8_t language,
                                   MessageFormat format = MF_FORMATTED) const;
  const std::vector<std::string>
  GetAllMessages(MessageFormat format = MF_FORMATTED) const;

private:
  std::vector<std::string> messages = {"", TODO_TRANSLATE, TODO_TRANSLATE};
  TextBoxType type = TEXTBOX_TYPE_BLACK;
  TextBoxPosition position = TEXTBOX_POS_BOTTOM;
  std::vector<std::string> colors = {};
  std::vector<bool> capital = {};
};
