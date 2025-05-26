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
#include <vector>

using namespace Rando;
namespace fs = std::filesystem;

std::array<HintText, RHT_MAX> Rando::StaticData::hintTextTable = {};

// Output data
fs::path _currentPath = fs::path(Utils::getExecutablePath());
fs::path g_output_dir = _currentPath.parent_path() / "output";

class JsonObject {
private:
  nlohmann::json create_json_pair(const std::string &key,
                                  const std::string &value) {
    nlohmann::json json;
    json[key.c_str()] = value.c_str();
    return json;
  }

public:
  JsonObject() : languages({}) {}
  std::array<std::vector<std::string>, LANGUAGE_MAX> languages;

  void insert(std::string &key, const CustomMessage &message) {
    this->languages[LANGUAGE_ENG].push_back(
        create_json_pair(key, message.GetForLanguage(LANGUAGE_ENG, MF_RAW)));
    this->languages[LANGUAGE_GER].push_back(
        create_json_pair(key, message.GetForLanguage(LANGUAGE_GER, MF_RAW)));
    this->languages[LANGUAGE_FRA].push_back(
        create_json_pair(key, message.GetForLanguage(LANGUAGE_FRA, MF_RAW)));
    // TODO: Figure out why JPN faults out
    // this->languages[LANGUAGE_JPN].push_back(nlohmann::json::object(
    //     {key, message.GetForLanguage(LANGUAGE_JPN, MF_RAW)}));
  }

  void insert(std::string &key, const std::vector<CustomMessage> &messages) {
    for (auto it = messages.begin(); it != messages.end(); it++) {
      this->languages[LANGUAGE_ENG].push_back(
          nlohmann::json{{key, (*it).GetForLanguage(LANGUAGE_ENG, MF_RAW)}});
      this->languages[LANGUAGE_GER].push_back(
          nlohmann::json{{key, (*it).GetForLanguage(LANGUAGE_GER, MF_RAW)}});
      this->languages[LANGUAGE_FRA].push_back(
          nlohmann::json{{key, (*it).GetForLanguage(LANGUAGE_FRA, MF_RAW)}});
      this->languages[LANGUAGE_JPN].push_back(
          nlohmann::json{{key, (*it).GetForLanguage(LANGUAGE_JPN, MF_RAW)}});
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
  for (int i = 0; i < argc; i++)
    std::cout << "  arv[" << i << "] = " << argv[i] << std::endl;

  StaticData::HintTable_Init_Exclude_Overworld();
  StaticData::HintTable_Init_Exclude_Dungeon();
  StaticData::HintTable_Init_Item();

  std::vector<std::string> all_hint_texts;
  JsonObject plain, ambiguous, obscure;
  std::cout << "RandomizerHintTextKey::RHT_JUNK01" << " - "
            << RandomizerHintTextKeyStrings[RandomizerHintTextKey::RHT_JUNK01]
            << std::endl;

  for (auto it = StaticData::hintTextTable.begin();
       it != StaticData::hintTextTable.end(); it++) {
    auto index = std::distance(std::begin(StaticData::hintTextTable), it);
    std::string key = RandomizerHintTextKeyStrings[index];
    if (key.empty()) {
      throw "Invalid key: " + key;
    }
    std::cout << "key: " << key << std::endl;
    plain.insert(key, (*it).getClearText());
    // ambiguous.insert(key, (*it).getAmbiguousText());
    // obscure.insert(key, (*it).getObscureText());
  }

  nlohmann::json hint_data;
  hint_data["hintCount"] = StaticData::hintTextTable.size();
  hint_data["hints"] = all_hint_texts;

  if (!fs::exists(g_output_dir)) {
    if (!fs::create_directory(g_output_dir)) {
      std::cout << "Error creating directory: " << strerror(errno) << std::endl;
      return -1;
    }
  }

  plain.write_to_file("plain.json", true);
  ambiguous.write_to_file("ambiguous.json");
  obscure.write_to_file("obscure.json");
}
