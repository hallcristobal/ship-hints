#include "./hints.hpp"
#include <string>

CustomMessage::CustomMessage(std::string english_, std::string german_,
                             std::string french_, TextBoxType type_,
                             TextBoxPosition position_)
    : type(type_), position(position_) {
  messages[LANGUAGE_ENG] = std::move(english_);
  messages[LANGUAGE_GER] = std::move(german_);
  messages[LANGUAGE_FRA] = std::move(french_);
}

CustomMessage::CustomMessage(std::string english_, std::string german_,
                             std::string french_,
                             std::vector<std::string> colors_,
                             std::vector<bool> capital_, TextBoxType type_,
                             TextBoxPosition position_) {
  messages[LANGUAGE_ENG] = std::move(english_);
  messages[LANGUAGE_GER] = std::move(german_);
  messages[LANGUAGE_FRA] = std::move(french_);
  colors = colors_;
  capital = capital_;
  type = type_;
  position = position_;
}

CustomMessage::CustomMessage(std::string english_, TextBoxType type_,
                             TextBoxPosition position_)
    : type(type_), position(position_) {
  messages[LANGUAGE_ENG] = std::move(english_);
}

CustomMessage::CustomMessage(std::string english_,
                             std::vector<std::string> colors_,
                             std::vector<bool> capital_, TextBoxType type_,
                             TextBoxPosition position_) {
  messages[LANGUAGE_ENG] = std::move(english_);
  colors = colors_;
  capital = capital_;
  type = type_;
  position = position_;
}

CustomMessage::CustomMessage(Text text, TextBoxType type_,
                             TextBoxPosition position_)
    : type(type_), position(position_) {
  messages[LANGUAGE_ENG] = text.GetEnglish();
  messages[LANGUAGE_GER] = text.GetGerman();
  messages[LANGUAGE_FRA] = text.GetFrench();
}
