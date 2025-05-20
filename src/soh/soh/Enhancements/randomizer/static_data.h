#pragma once

#include "randomizerTypes.h"
#include <array>

namespace Rando {
class StaticData {
public:
  static std::array<HintText, RHT_MAX> hintTextTable;

  static void HintTable_Init_Exclude_Overworld();
  static void HintTable_Init_Exclude_Dungeon();
  static void HintTable_Init_Item();
};
} // namespace Rando
