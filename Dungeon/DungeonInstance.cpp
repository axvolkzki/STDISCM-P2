#include "DungeonInstance.h"

#include <thread>
#include <chrono>

DungeonInstance::DungeonInstance(int id) : instanceID(id), active(false), totalServed(0), totalTimeServed(0) {}

void DungeonInstance::executeParty(int partyID, int duration) {
    std::lock_guard<std::mutex> lock(instanceMutex);
    active = true;
    totalServed++;
    totalTimeServed += duration;

    std::cout << "[Active] Instance " << instanceID << " executing Party " << partyID
        << " for " << duration << "s." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(duration)); // Simulate execution

    active = false;
}

bool DungeonInstance::isActive() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    return active;
}

void DungeonInstance::printStatus() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    std::cout << "[" << (active ? "Active" : "Empty") << "] Instance " << instanceID << std::endl;
}

void DungeonInstance::printSummary() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    std::cout << "\nInstance " << instanceID << " Summary:\n"
        << "Served Parties: " << totalServed << "\n"
        << "Total Time Served: " << totalTimeServed << "s\n" << std::endl;
}

int DungeonInstance::getInstanceID() const {
    return instanceID;
}