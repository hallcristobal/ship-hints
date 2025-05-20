#include "./static_data.h"
#include <iostream>

static Rando::StaticData g_staticData = Rando::StaticData();
int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++)
    std::cout << "  arv[" << i << "] = " << argv[i] << std::endl;

  g_staticData.HintTable_Init_Exclude_Overworld();
  g_staticData.HintTable_Init_Exclude_Dungeon();
  g_staticData.HintTable_Init_Item();

  std::cout << "static data hint len: " << g_staticData.hintTextTable.size()
            << std::endl;
}
