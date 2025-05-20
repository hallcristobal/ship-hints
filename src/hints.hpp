#pragma once

#include "text.hpp"
#ifndef MESSAGE_DATA_TEXTBOX_TYPES_H
#define MESSAGE_DATA_TEXTBOX_TYPES_H

typedef enum {
  /*  0 */ TEXTBOX_TYPE_BLACK,
  /*  1 */ TEXTBOX_TYPE_WOODEN,
  /*  2 */ TEXTBOX_TYPE_BLUE,
  /*  3 */ TEXTBOX_TYPE_OCARINA,
  /*  4 */ TEXTBOX_TYPE_NONE_BOTTOM,
  /*  5 */ TEXTBOX_TYPE_NONE_NO_SHADOW,
  /* 11 */ TEXTBOX_TYPE_CREDITS = 11
} TextBoxType;

typedef enum {
  /* 0 */ TEXTBOX_BG_CROSS
} TextBoxBackground;

typedef enum {
  /* 0 */ TEXTBOX_POS_VARIABLE,
  /* 1 */ TEXTBOX_POS_TOP,
  /* 2 */ TEXTBOX_POS_MIDDLE,
  /* 3 */ TEXTBOX_POS_BOTTOM
} TextBoxPosition;

typedef enum {
    LANGUAGE_ENG,
    LANGUAGE_GER,
    LANGUAGE_FRA,
    LANGUAGE_JPN,
    LANGUAGE_MAX
} Language;
#define TODO_TRANSLATE "TranslateThis"

#endif

#define QM_WHITE "\x00"s
#define QM_RED "\x41"
#define QM_GREEN "\x42"
#define QM_BLUE "\x43"
#define QM_LBLUE "\x44"
#define QM_PINK "\x45"
#define QM_YELLOW "\x46"
#define QM_BLACK "\x47"

#define HS_HORSE_ARCHERY "\x00"s // HS_HBA is an enum already

#include <string>
#include <vector>

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

private:
  std::vector<std::string> messages = {"", TODO_TRANSLATE, TODO_TRANSLATE};
  TextBoxType type = TEXTBOX_TYPE_BLACK;
  TextBoxPosition position = TEXTBOX_POS_BOTTOM;
  std::vector<std::string> colors = {};
  std::vector<bool> capital = {};
};

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
