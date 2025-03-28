#pragma once
#include <memory>
#include <limits>

#include "../Utility/TypeDefRepo.h"
#include "../Utility/Colors.h"

class GlobalConfig
{
public:
    static GlobalConfig* getInstance();

    static void initialize();
    static void destroy();

    bool askForPartyQueueConfig();
    void printPartyQueueConfig();

	int getMaxInstances() const { return partyQueueConfig.n; }
	int getTankPlayers() const { return partyQueueConfig.t; }
	int getHealerPlayers() const { return partyQueueConfig.h; }
	int getDPSPlayers() const { return partyQueueConfig.d; }
	int getMinTime() const { return partyQueueConfig.t1; }
	int getMaxTime() const { return partyQueueConfig.t2; }
	int getMaxNumParties() const { return maxNumParties; }

private:
    GlobalConfig();
    static GlobalConfig* sharedInstance;

    struct Configuration
    {
        unsigned int n;      // maximum number of concurrent instances
        unsigned int t;      // number of tank players in the queue
        unsigned int h;      // number of healer players in the queue
        unsigned int d;      // number of DPS players in the queue
        unsigned int t1;     // minimum time before an instance is finished
        unsigned int t2;     // maximum time before an instance is finished
    };

    Configuration partyQueueConfig;
    Colors color;
    bool isConfigured;
    int maxNumParties;

    bool isValidInt(const std::string& input, unsigned int& output);
    int getValidInt();
    int getValidMaxTime(unsigned int minTime);

	int computeMaxParties(int tanks, int healers, int dps);
    void configurePartyQueue(unsigned int n, unsigned int t, unsigned int h, unsigned int d, unsigned int t1, unsigned int t2);

};
