#include "DungeonInstance.h"

#include <thread>
#include <chrono>

using namespace std;

DungeonInstance::DungeonInstance(int id) : instanceID(id), active(false), totalServed(0), totalTimeServed(0) {}

void DungeonInstance::executeParty(int partyID, int duration) {
    std::lock_guard<std::mutex> lock(instanceMutex);
    active = true;
    totalServed++;
    totalTimeServed += duration;

	std::lock_guard<std::mutex> lock2(std::mutex());                // Lock to prevent interleaving of output
	this->active ? this->color.green() : this->color.red();
    cout << "[Active] Instance " << instanceID << " executing Party " << partyID << " for " << duration << "s." << endl;

    std::this_thread::sleep_for(std::chrono::seconds(duration));    // Simulate execution

    active = false;
}

bool DungeonInstance::isActive() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    return active;
}

void DungeonInstance::printStatus() {
    std::lock_guard<std::mutex> lock(instanceMutex);
	this->active ? this->color.green() : this->color.red();
    cout << "[" << (active ? "Active" : "Empty") << "] Instance " << instanceID << endl;
}

void DungeonInstance::printSummary() {
    std::lock_guard<std::mutex> lock(instanceMutex);
	this->color.yellow();
    cout << "Instance " << instanceID << endl;
    cout << "\tServed Parties       : " << totalServed << endl;
    cout << "\tTotal Time Served    : " << totalTimeServed << "s." << endl;
	this->color.reset();
}

int DungeonInstance::getInstanceID() const {
    return instanceID;
}