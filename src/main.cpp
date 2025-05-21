#include "soh/soh/Enhancements/randomizer/3drando/hints.hpp"
#include "soh/soh/Enhancements/randomizer/randomizerTypes.h"
#include "soh/soh/Enhancements/randomizer/static_data.h"

#include <iostream>
std::array<HintText, RHT_MAX> Rando::StaticData::hintTextTable = {};

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++)
    std::cout << "  arv[" << i << "] = " << argv[i] << std::endl;

  Rando::StaticData::HintTable_Init_Exclude_Overworld();
  Rando::StaticData::HintTable_Init_Exclude_Dungeon();
  Rando::StaticData::HintTable_Init_Item();

  std::cout << "static data hint len: "
            << Rando::StaticData::hintTextTable.size() << std::endl;
}
