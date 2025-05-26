#include "message_data_textbox_types.h"
#include "nlohmann/json_fwd.hpp"
#include "soh/soh/Enhancements/custom-message/CustomMessageManager.h"
#include "soh/soh/Enhancements/randomizer/randomizerTypes.h"
#include "soh/soh/Enhancements/randomizer/static_data.h"
#include "utils.hpp"

#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <vector>

using namespace Rando;
namespace fs = std::filesystem;
std::array<HintText, RHT_MAX> Rando::StaticData::hintTextTable = {};

fs::path g_output_dir =
    fs::path(Utils::getExecutablePath()).parent_path() / "output";

#define LOG(...) Utils::log(__PRETTY_FUNCTION__, __VA_ARGS__)
#define ELOG(...)                                                              \
  Utils::log(__PRETTY_FUNCTION__, __VA_ARGS__, Utils::LogFlags::ERROR)

class JsonObject {
private:
public:
  JsonObject() : languages({}) {}
  std::array<nlohmann::json, LANGUAGE_MAX> languages = {
      nlohmann::json::object(),
      nlohmann::json::object(),
      nlohmann::json::object(),
      nlohmann::json::object(),
  };

  nlohmann::json create_json_pair(const std::string &key,
                                  const std::string &value) {
    nlohmann::json json;
    json[key] = value;
    return json;
  }

  void insert(std::string &key, const CustomMessage &message) {
    std::string eng_string = message.GetForLanguage(LANGUAGE_ENG, MF_RAW);
    // LOG("key : '" + key + "' - message: '" + eng_string + "'");
    if (eng_string.empty()) {
      return;
    }

    // clang-format off
    this->languages[LANGUAGE_ENG][key] =message.GetForLanguage(LANGUAGE_ENG, MF_RAW);
    this->languages[LANGUAGE_GER][key] =message.GetForLanguage(LANGUAGE_GER, MF_RAW);
    this->languages[LANGUAGE_FRA][key] =message.GetForLanguage(LANGUAGE_FRA, MF_RAW);
    // TODO: Why does inserting into JPN seg fault?
    // this->languages[LANGUAGE_JPN][key] =message.GetForLanguage(LANGUAGE_JPN, MF_RAW);
    // clang-format on
  }

  void insert(std::string &key, const std::vector<CustomMessage> &messages) {
    for (auto it = messages.begin(); it != messages.end(); it++) {
      // clang-format off
      this->languages[LANGUAGE_ENG][key] = (*it).GetForLanguage(LANGUAGE_ENG, MF_RAW);
      this->languages[LANGUAGE_GER][key] = (*it).GetForLanguage(LANGUAGE_GER, MF_RAW);
      this->languages[LANGUAGE_FRA][key] = (*it).GetForLanguage(LANGUAGE_FRA, MF_RAW);
      // TODO: Why does inserting into JPN seg fault?
      // this->languages[LANGUAGE_JPN][key] = (*it).GetForLanguage(LANGUAGE_JPN, MF_RAW);
      // clang-format on
    }
  }

  nlohmann::json to_json() {
    nlohmann::json json;
    json["en"] = this->languages[LANGUAGE_ENG];
    json["de"] = this->languages[LANGUAGE_GER];
    json["fr"] = this->languages[LANGUAGE_FRA];
    json["jp"] = this->languages[LANGUAGE_JPN];
    return json;
  }

  void write_to_file(std::string fileName, bool format = false) {
    std::ofstream outputFile(g_output_dir / fileName);
    outputFile << this->to_json().dump(format ? 2 : -1, ' ', false,
                                       nlohmann::json::error_handler_t::ignore)
               << std::endl;
    outputFile.close();
  }
};

int main(int argc, char **argv) {
  StaticData::HintTable_Init_Exclude_Overworld();
  StaticData::HintTable_Init_Exclude_Dungeon();
  StaticData::HintTable_Init_Item();

  JsonObject plain, ambiguous, obscure;

  for (auto it = StaticData::hintTextTable.begin();
       it != StaticData::hintTextTable.end(); it++) {
    auto index = std::distance(std::begin(StaticData::hintTextTable), it);
    std::string key = RandomizerHintTextKeyStrings[index];
    if (key.empty()) {
      throw "Invalid key: " + key;
    }
    plain.insert(key, (*it).getClearText());
    ambiguous.insert(key, (*it).getAmbiguousText());
    obscure.insert(key, (*it).getObscureText());
  }

  if (!fs::exists(g_output_dir)) {
    if (!fs::create_directory(g_output_dir)) {
      std::stringstream ss("Error creating directory: ");
      ss << strerror(errno);
      ELOG(ss.str());
      return -1;
    }
  }

  plain.write_to_file("plain.json");
  ambiguous.write_to_file("ambiguous.json");
  obscure.write_to_file("obscure.json");
}
