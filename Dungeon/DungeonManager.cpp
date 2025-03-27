#include "DungeonManager.h"
#include "../Config/GlobalConfig.h"
#include <iostream>

using namespace std;
DungeonManager* DungeonManager::sharedInstance = nullptr;

DungeonManager::DungeonManager()
	: instanceSemaphore(GlobalConfig::getInstance()->getMaxInstances())
{
	this->maxInstances = GlobalConfig::getInstance()->getMaxInstances();
	this->maxParties = GlobalConfig::getInstance()->getMaxNumParties();
	this->tankCount = GlobalConfig::getInstance()->getTankPlayers();
	this->healerCount = GlobalConfig::getInstance()->getHealerPlayers();
	this->dpsCount = GlobalConfig::getInstance()->getDPSPlayers();
	this->stopProcessing = false;

	for (int i = 0; i < this->maxInstances; i++) {
		instances.push_back(new DungeonInstance(i));
	}
}

std::pair<int, int> DungeonManager::fetchNextPartyFromQueue()
{
    std::unique_lock<std::mutex> lock(queueMutex);
    instanceNotifier.wait(lock, [this] { return stopProcessing || !partyQueue.empty(); });

    if (stopProcessing && partyQueue.empty()) return { -1, -1 }; // Return invalid pair to indicate exit.

    auto [partyID, duration] = partyQueue.top();
    partyQueue.pop();
    return { partyID, duration };
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
	// cout << "[DEBUGGER] DungeonManager initialized!" << endl;
}

void DungeonManager::destroy() {
    delete sharedInstance;
    sharedInstance = nullptr;
}

void DungeonManager::addPartyToQueue(int partyID, int duration) {
    std::lock_guard<std::mutex> lock(queueMutex);
    partyQueue.emplace(partyID, duration);
	instanceNotifier.notify_one(); // Notify waiting threads to start processing
}


void DungeonManager::processParties() {
    std::vector<std::thread> instanceThreads;

	// Create threads for each instance
    for (auto& instance : instances) {
        instanceThreads.emplace_back([this, instance]() {
            while (true) {
                auto [partyID, duration] = fetchNextPartyFromQueue();
                if (partyID == -1) return;                      // Stop execution if no more parties

				instanceSemaphore.acquire();                    // Acquire semaphore to limit number of instances
                instance->executeParty(partyID, duration);
				instanceSemaphore.release();                    // Release semaphore to allow other instances to execute
            }
        });
    }

	// Sleep for 1 second before stopping processing
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopProcessing = true;
    }
    instanceNotifier.notify_all(); // Wake up all waiting threads

    // Join all threads before printing summary
    for (auto& thread : instanceThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void DungeonManager::printInstanceStatus() {
	this->color.yellow();
	std::lock_guard<std::mutex> lock(printMutex);
    cout << "\nCurrent Dungeon Instances:\n";
    for (auto& instance : instances) {
        instance->printStatus();
    }
	this->color.reset();
}


void DungeonManager::printSummary()
{
	std::lock_guard<std::mutex> lock(printMutex);
	this->color.yellow();
    cout << "\n---- Dungeon Execution Summary ----\n";
    cout << "-----------------------------------" << endl;
    cout << "Max Instances      : " << this->maxInstances << endl;
    cout << "Max Parties        : " << this->maxParties << endl;
    cout << "Remaining Tanks    : " << this->tankCount - this->maxParties << endl;
    cout << "Remaining Healers  : " << this->healerCount - this->maxParties << endl;
    cout << "Remaining DPS      : " << this->dpsCount - (this->maxParties * 3) << endl;

	cout << "\nSummary of Instances:" << endl;
	for (auto& instance : instances) {
		instance->printSummary();
	}

	cout << "-----------------------------------" << endl;
	this->color.reset();
}


