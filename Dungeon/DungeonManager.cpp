#include "DungeonManager.h"
#include "../Config/GlobalConfig.h"
#include <iostream>

using namespace std;
DungeonManager* DungeonManager::sharedInstance = nullptr;

DungeonManager::DungeonManager()
	: instanceSemaphore(GlobalConfig::getInstance()->getMaxInstances())  // Correct way to initialize
{
	this->maxInstances = GlobalConfig::getInstance()->getMaxInstances();
	this->maxParties = GlobalConfig::getInstance()->getMaxNumParties();
	this->tankCount = GlobalConfig::getInstance()->getTankPlayers();
	this->healerCount = GlobalConfig::getInstance()->getHealerPlayers();
	this->dpsCount = GlobalConfig::getInstance()->getDPSPlayers();

	for (int i = 0; i < this->maxInstances; i++) {
		instances.push_back(new DungeonInstance(i));
	}
}

DungeonManager* DungeonManager::getInstance() {
	if (sharedInstance == nullptr) {
		sharedInstance = new DungeonManager();
	}

	return sharedInstance;
}

void DungeonManager::initialize() {
    if (sharedInstance == nullptr) {
        sharedInstance = new DungeonManager();
    }

    // Debugger
	cout << "[DEBUGGER] DungeonManager initialized!" << endl;
}

void DungeonManager::destroy() {
    delete sharedInstance;
    sharedInstance = nullptr;
}

void DungeonManager::addPartyToQueue(int partyID, int duration) {
    std::lock_guard<std::mutex> lock(queueMutex);
    partyQueue.push({ partyID, duration });
    instanceNotifier.notify_one(); // Notify waiting threads
}


void DungeonManager::processParties() {
    std::vector<std::thread> instanceThreads;

    while (!partyQueue.empty()) {
        instanceSemaphore.acquire(); // Wait for an available instance

        queueMutex.lock();
        auto [partyID, duration] = partyQueue.front();
        partyQueue.pop();
        queueMutex.unlock();

        instanceThreads.emplace_back([this, partyID, duration]() {
            for (auto& instance : instances) {
                if (!instance->isActive()) {
                    instance->executeParty(partyID, duration);
                    instanceSemaphore.release(); // Release instance when done
                    break;
                }
            }
            });
    }

    // Join all threads before printing summary
    for (auto& thread : instanceThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void DungeonManager::printInstanceStatus() {
    cout << "\nCurrent Dungeon Instances:\n";
    for (auto& instance : instances) {
        instance->printStatus();
    }
}


void DungeonManager::printSummary()
{
    cout << "\n--- Dungeon Execution Summary ---\n";
    cout << "----------------------" << endl;
    cout << "Max Instances      : " << this->maxInstances << endl;
    cout << "Max Parties        : " << this->maxParties << endl;
    cout << "Remaining Tanks    : " << this->tankCount - this->maxParties << endl;
    cout << "Remaining Healers  : " << this->healerCount - this->maxParties << endl;
    cout << "Remaining DPS      : " << this->dpsCount - (this->maxParties * 3) << endl;

	for (auto& instance : instances) {
		instance->printSummary();
	}
}


