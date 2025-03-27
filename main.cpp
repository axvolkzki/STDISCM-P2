#include "Utility/TypeDefRepo.h"
#include "Config/GlobalConfig.h"
#include "Dungeon/DungeonManager.h"

// Function Prototypes
int randomInt(int min, int max);
int displayBanner();

// Main Function
int main() {
    // Variables
    bool running = true;
    bool isConfigured = false;
	int maxInstance = 0;

	// Display banner
	displayBanner();

    // Configure
    GlobalConfig::initialize();
    isConfigured = GlobalConfig::getInstance()->askForPartyQueueConfig();
    GlobalConfig::getInstance()->printPartyQueueConfig();

	// DungeonManager
    DungeonManager::initialize();
	DungeonManager::getInstance()->printInstanceStatus();
    

	// Form party based on configuration
	int maxParties = GlobalConfig::getInstance()->getMaxNumParties();
	for (int i = 0; i < maxParties; i++) {
		int duration = randomInt(GlobalConfig::getInstance()->getMinTime(), GlobalConfig::getInstance()->getMaxTime());
		DungeonManager::getInstance()->addPartyToQueue(i, duration);
	}
    
	cout << "[SYSTEM] All parties have been formed and added to the queue!\n" << endl;

	// Start processing parties
	DungeonManager::getInstance()->processParties();

	// Wait for 5 seconds
    this_thread::sleep_for(std::chrono::seconds(5));

	// Print summary
	DungeonManager::getInstance()->printSummary();

    // Destroy
    GlobalConfig::destroy();
    DungeonManager::destroy();


    return 0;
}

// Function Definitions
int randomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

int displayBanner() {
	cout << "---------------------------------------------------" << endl;
	cout << "------------- Welcome to Dungeon Party ------------" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << endl;
	cout << "Developed by: ABENOJA, Amelia Joyce L.		S14" << endl;
	cout << endl;
	cout << endl;
	return 0;
}