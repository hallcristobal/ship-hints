#pragma once
#include "../../../include/message_data_textbox_types.h"
#include "../randomizer/3drando/text.hpp"
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
                  TextBoxType type_ = TEXTBOX_TYPE_BLACK, TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
    CustomMessage(std::string english_, std::string german_, std::string french_, std::vector<std::string> colors_,
                  std::vector<bool> capital_ = {}, TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                  TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
    CustomMessage(std::string english_, TextBoxType type_ = TEXTBOX_TYPE_BLACK,
                  TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
    CustomMessage(std::string english_, std::vector<std::string> colors_, std::vector<bool> capital_ = {},
                  TextBoxType type_ = TEXTBOX_TYPE_BLACK, TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);
    CustomMessage(Text text, TextBoxType type_ = TEXTBOX_TYPE_BLACK, TextBoxPosition position_ = TEXTBOX_POS_BOTTOM);

    static CustomMessage LoadVanillaMessageTableEntry(uint16_t textId);

    static std::string MESSAGE_END();
    static std::string ITEM_OBTAINED(uint8_t x);
    static std::string NEWLINE();
    static std::string COLOR(std::string x);
    static std::string POINTS(std::string x); // HIGH_SCORE is also a macro
    static std::string WAIT_FOR_INPUT();
    static std::string PLAYER_NAME();

    const std::string GetEnglish(MessageFormat format = MF_FORMATTED) const;
    const std::string GetFrench(MessageFormat format = MF_FORMATTED) const;
    const std::string GetGerman(MessageFormat format = MF_FORMATTED) const;
    const std::string GetForCurrentLanguage(MessageFormat format = MF_FORMATTED) const;
    const std::string GetForLanguage(uint8_t language, MessageFormat format = MF_FORMATTED) const;
    const std::vector<std::string> GetAllMessages(MessageFormat format = MF_FORMATTED) const;
    void ProcessMessageFormat(std::string& str, MessageFormat format) const;
    const std::vector<std::string>& GetColors() const;
    void SetColors(std::vector<std::string> colors_);
    const std::vector<bool>& GetCapital() const;
    void SetCapital(std::vector<bool> capital_);
    const TextBoxType& GetTextBoxType() const;
    void SetTextBoxType(TextBoxType boxType);
    const TextBoxPosition& GetTextBoxPosition() const;

    CustomMessage operator+(const CustomMessage& right) const;
    CustomMessage operator+(const std::string& right) const;
    void operator+=(const std::string& right);
    void operator+=(const CustomMessage& right);
    bool operator==(const CustomMessage& operand) const;
    bool operator==(const std::string& operand) const;
    bool operator!=(const CustomMessage& right) const;

    /**
     * @brief Finds an instance of oldStr in each language of the CustomMessage
     * and replaces it with newStr. Typically used for dynamic variable replacement
     * (i.e. gameplay stats, skulltula count)
     *
     * @param oldStr the string to be replaced
     * @param newStr the string to replace with
     */
    void Replace(std::string&& oldStr, std::string&& newStr);

    /**
     * @brief Finds an instance of oldStr in each language of the CustomMessage,
     * and replaces it with the corresponding string in the provided CustomMessage.
     * Typically used for dynamic variable replacement (i.e. gameplay stats, skulltula count)
     *
     * @param oldStr the string to be replaced
     * @param newMessage the message containing the new strings.
     */
    void Replace(std::string&& oldStr, CustomMessage newMessage);

    /**
     * @brief Capitalizes the first letter of the string for each language.
     */
    void Capitalize();

    /**
     * @brief Replaces special characters (things like diacritics for non-english langugages)
     * with the control codes used to display them in OoT's textboxes.
     */
    void ReplaceSpecialCharacters(std::string& str) const;

    /**
     * @brief Replaces hashtags with stored colors.
     */
    void EncodeColors(std::string& str) const;

    /**
     * @brief Replaces our color variable strings with the OoT control codes.
     */
    void ReplaceColors(std::string& str) const;

    /**
     * @brief Replaces `$<char>` variable strings with OoT control codes.
     */
    void ReplaceAltarIcons(std::string& str) const;

    /**
     * @brief Replaces [[1]] style variable strings with the provided vector of customMessages
     */
    void InsertNames(std::vector<CustomMessage> toInsert);

    /**
     * @brief Replaces various symbols with the control codes necessary to
     * display them in OoT's textboxes. i.e. special characters, colors, newlines,
     * wait for input, etc. Also adds the item icon to each page of the textbox.
     *
     * @param iid the ItemID whose icon should be displayed in this message's textbox.
     */
    void Format(ItemID iid);

    /**
     * @brief Replaces [[d]] in text with the supplied number, and if plural
     * options exist (2 blocks of text surrounded by |) choose the former if it 1,
     * and the latter otherwise, deleting the other and the |'s.
     *
     * @param num the number to insert.
     */
    void InsertNumber(uint8_t num);

    /**
     * @brief Replaces various symbols with the control codes necessary to
     * display them in OoT's textboxes. i.e. special characters, colors, newlines,
     * wait for input, etc.
     */
    void Format();

    /**
     * @brief formats the message specifically to fit in OoT's
     * textboxes, and use it's formatting.
     */
    void AutoFormat();

    /**
     * @brief Removes all OoT formatting from the message,
     * making it a good form for writing into spoiler logs.
     */
    void Clean();

    /**
     * @brief Replaces variable characters with fixed ones to store the sata in string form
     */
    void Encode();

    /**
     * @brief Replaces various symbols with the control codes necessary to
     * display them in OoT's textboxes for a single string
     * . i.e. special characters, colors, newlines, wait for input, etc.
     */
    void FormatString(std::string& str) const;

    /**
     * @brief finds NEWLINEs in a string, while filtering
     * /x01's that are used as opperands
     */
    size_t FindNEWLINE(std::string& str, size_t lastNewline) const;

    /**
     * @brief Inserts a string into another string, following the rules
     * of auto-format inserting new lines: spaces and & are replaced while
     * other chars are appended to.
     *
     * @param str the string we are inserting into
     * @param pos the position in the string to insert
     * @param breakString the string we are inserting
     */
    bool AddBreakString(std::string& str, size_t pos, std::string breakString) const;

    /**
     * @brief formats the string specifically to fit in OoT's
     * textboxes, and use it's formatting.
     * RANDOTODO whoever knows exactly what this does check my adaption
     */
    void AutoFormatString(std::string& str) const;

    /**
     * @brief Removes symbols used for control codes from the string,
     * leaving raw text
     */
    void CleanString(std::string& str) const;

  private:
    std::vector<std::string> messages = { "", TODO_TRANSLATE, TODO_TRANSLATE };
    TextBoxType type = TEXTBOX_TYPE_BLACK;
    TextBoxPosition position = TEXTBOX_POS_BOTTOM;
    std::vector<std::string> colors = {};
    std::vector<bool> capital = {};
};

