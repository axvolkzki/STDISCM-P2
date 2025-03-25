#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore>


#include "../Utility/TypeDefRepo.h"
#include "../Utility/Colors.h"
#include "DungeonInstance.h"

class DungeonManager
{
public:
    static DungeonManager* getInstance();

    static void initialize();
    static void destroy();

    void addPartyToQueue(int partyID, int duration);
    void processParties();
    void printInstanceStatus();
    void printSummary();

private:
    DungeonManager();

    Colors color;
    static DungeonManager* sharedInstance;
    
    int maxInstances;
	int maxParties;
	int tankCount;
	int healerCount;
	int dpsCount;
    
    std::vector<DungeonInstance*> instances;
    std::queue<std::pair<int, int>> partyQueue; // Pair of (partyID, duration)

    std::mutex queueMutex;
    std::condition_variable instanceNotifier;
    std::counting_semaphore<> instanceSemaphore;
};

