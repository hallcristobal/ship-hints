#include "soh/soh/Enhancements/randomizer/static_data.h"

#include <iostream>
#include <nlohmann/json.hpp>

std::array<HintText, RHT_MAX> Rando::StaticData::hintTextTable = {};
using namespace Rando;

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++)
    std::cout << "  arv[" << i << "] = " << argv[i] << std::endl;

  StaticData::HintTable_Init_Exclude_Overworld();
  StaticData::HintTable_Init_Exclude_Dungeon();
  StaticData::HintTable_Init_Item();

  std::cout << "static data hint len: " << StaticData::hintTextTable.size()
            << std::endl;

  nlohmann::json hint_data;
  hint_data["hintCount"] = StaticData::hintTextTable.size();

  std::cout << hint_data.dump(2) << std::endl;
}
