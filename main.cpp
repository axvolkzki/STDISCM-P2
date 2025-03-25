#include "Utility/TypeDefRepo.h"
#include "Config/GlobalConfig.h"
//#include "Dungeon/DungeonManager.h"

int main() {
    // Variables
    bool running = true;
    bool isConfigured = false;
    int maxDungeon = 0;

    // Configure
    GlobalConfig::initialize();
    isConfigured = GlobalConfig::getInstance()->askForPartyQueueConfig();
    GlobalConfig::getInstance()->printPartyQueueConfig();

    // DungeonManager
    maxDungeon = GlobalConfig::getInstance()->getMaxDungeon();
    /*DungeonManager::initialize(maxDungeon);*/


    // Main loop
    while (running && isConfigured) {
        running = false;
    }

    // Destroy
    GlobalConfig::destroy();
    /*DungeonManager::destroy();*/


    return 0;
}