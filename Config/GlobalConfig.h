#pragma once
#include <memory>
#include <limits>

#include "../Utility/TypeDefRepo.h"

class GlobalConfig
{
public:
    static GlobalConfig* getInstance();

    static void initialize();
    static void destroy();

    bool askForPartyQueueConfig();
    void printPartyQueueConfig();

    int getMaxDungeon();

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
    bool isConfigured;

    bool isValidInt(const std::string& input, unsigned int& output);
    int getValidInt();

    void configurePartyQueue(unsigned int n, unsigned int t, unsigned int h, unsigned int d, unsigned int t1, unsigned int t2);

};
