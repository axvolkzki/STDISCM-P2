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
    bool stopProcessing;
    
    std::vector<DungeonInstance*> instances;
    
    struct CompareParty {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;  // Min-heap: shortest duration first
        }
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CompareParty> partyQueue;
	

	std::mutex queueMutex;						    // Mutex for queue
	std::mutex printMutex;                          // Mutex for printing
	std::condition_variable instanceNotifier;       // Notifier for instances
	std::counting_semaphore<> instanceSemaphore;    // Semaphore to limit number of instances

	std::pair<int, int> fetchNextPartyFromQueue();
};

