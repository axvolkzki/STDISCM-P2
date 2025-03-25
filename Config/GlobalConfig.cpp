#include "GlobalConfig.h"
#include <iostream>

using namespace std;
GlobalConfig* GlobalConfig::sharedInstance = nullptr;

GlobalConfig::GlobalConfig() {
    // Set default configuration
    // this->configurePartyQueue(10, 2, 2, 6);
    this->configurePartyQueue(0, 0, 0, 0, 0, 0);
    this->isConfigured = false;
}

GlobalConfig* GlobalConfig::getInstance() {
    if (GlobalConfig::sharedInstance == nullptr) {
        GlobalConfig::sharedInstance = new GlobalConfig();
    }

    return GlobalConfig::sharedInstance;
}

void GlobalConfig::initialize() {
    if (sharedInstance == nullptr) {
        sharedInstance = new GlobalConfig();
    }
}

void GlobalConfig::destroy() {
    if (sharedInstance != nullptr) {
        delete sharedInstance;
        sharedInstance = nullptr;
    }
}

bool GlobalConfig::askForPartyQueueConfig() {
    unsigned long int n, t, h, d, t1, t2;

    cout << "Enter the maximum number of concurrent instances: ";
    n = getValidInt();

    cout << "Enter the number of tank players in the queue: ";
    t = getValidInt();

    cout << "Enter the number of healer players in the queue: ";
    h = getValidInt();

    cout << "Enter the number of DPS players in the queue: ";
    d = getValidInt();

    cout << "Enter the minimum time before an instance is finished: ";
    t1 = getValidInt();

    cout << "Enter the maximum time before an instance is finished: ";
    t2 = getValidInt();


    if (n <= 0 && t <= 0 && h <= 0 && d <= 0 && t1 <= 0 && t2 <= 0) {
        std::cout << "Configuration failed. All values must be greater than 0." << std::endl;
        this->isConfigured = false;
    }
    else {
        std::cout << "Configuration successful." << std::endl;
        this->configurePartyQueue(n, t, h, d, t1, t2);
        this->isConfigured = true;
    }

    return this->isConfigured;
}

bool GlobalConfig::isValidInt(const std::string& input, unsigned int& output)
{
    if (input.empty()) {
        return false;
    }

    // Ensure all characters are digits
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }

    try {
        size_t pos;
        unsigned long long tempValue = std::stoull(input, &pos);

        // Ensure full conversion and check if value is within unsigned int range
        if (pos != input.length() || tempValue > std::numeric_limits<unsigned int>::max() || tempValue == 0) {
            return false;
        }

        output = static_cast<unsigned int>(tempValue);
        return true;
    }
    catch (const std::out_of_range&) {
        std::cerr << "Error: Number out of range.\n";
        return false;
    }
    catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid input.\n";
        return false;
    }
}

int GlobalConfig::getValidInt()
{
    std::string input;
    unsigned int number;

    while (true) {
        std::cout << "Enter a valid unsigned integer: ";
        std::cin >> input;

        if (isValidInt(input, number)) {
            return number;
        }
        else {
            std::cerr << "Invalid input. Please enter a valid unsigned integer.\n";
        }
    }
}


void GlobalConfig::configurePartyQueue(unsigned int n, unsigned int t, unsigned int h, unsigned int d, unsigned int t1, unsigned int t2) {
    this->partyQueueConfig.n = n;
    this->partyQueueConfig.t = t;
    this->partyQueueConfig.h = h;
    this->partyQueueConfig.d = d;
    this->partyQueueConfig.t1 = t1;
    this->partyQueueConfig.t2 = t2;
}

void GlobalConfig::printPartyQueueConfig() {
    cout << "Party Queue Configuration" << endl;
    cout << "------------------------" << endl;
    cout << "Maximum number of concurrent instances: " << this->partyQueueConfig.n << endl;
    cout << "Number of tank players in the queue: " << this->partyQueueConfig.t << endl;
    cout << "Number of healer players in the queue: " << this->partyQueueConfig.h << endl;
    cout << "Number of DPS players in the queue: " << this->partyQueueConfig.d << endl;
    cout << "Minimum time before an instance is finished: " << this->partyQueueConfig.t1 << endl;
    cout << "Maximum time before an instance is finished: " << this->partyQueueConfig.t2 << endl;
    cout << endl;
}

int GlobalConfig::getMaxDungeon()
{
    return this->partyQueueConfig.n;
}
