#pragma once
#include <iostream>
#include <mutex>

class DungeonInstance {
public:
    DungeonInstance(int id);
    void executeParty(int partyID, int duration);
    bool isActive();
    void printStatus();
    void printSummary();

    int getInstanceID() const;

private:
    int instanceID;
    bool active;
    int totalServed;
    int totalTimeServed;
	std::mutex instanceMutex;
};
