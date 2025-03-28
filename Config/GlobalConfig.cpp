#include "GlobalConfig.h"
#include <iostream>



using namespace std;
GlobalConfig* GlobalConfig::sharedInstance = nullptr;

GlobalConfig::GlobalConfig() {
    this->configurePartyQueue(0, 0, 0, 0, 0, 0);
	this->maxNumParties = 0;
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

    this->color.blue();
    cout << "Enter the following with positive integer only!" << endl;
    this->color.reset();

    cout << "Maximum number of concurrent instances         : ";
    n = getValidInt();

    cout << "Number of tank players in the queue            : ";
    t = getValidInt();

    cout << "Number of healer players in the queue          : ";
    h = getValidInt();

    cout << "Number of DPS players in the queue             : ";
    d = getValidInt();

    cout << "Minimum time before an instance is finished    : ";
    t1 = getValidInt();

    cout << "Maximum time before an instance is finished    : ";
	t2 = getValidMaxTime(t1);


    if (n <= 0 && t <= 0 && h <= 0 && d <= 0 && t1 <= 0 && t2 <= 0) {
        cout << "Configuration failed. All values must be greater than 0." << endl;
        this->isConfigured = false;
    }
	else {
		cout << endl;
		this->color.green();
        cout << "[SYSTEM] Configuration successful." << endl;
		this->color.reset();
        this->configurePartyQueue(n, t, h, d, t1, t2);
        this->isConfigured = true;
		this->maxNumParties = this->computeMaxParties(t, h, d);
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
        this->color.red();
        cerr << "Error: Number out of range.\n";
        this->color.reset();
        return false;
    }
    catch (const std::invalid_argument&) {
        this->color.red();
        cerr << "Error: Invalid input.\n";
        this->color.reset();
        return false;
    }
}

int GlobalConfig::getValidInt()
{
    String input;
    unsigned int number;

    while (true) {
        cin >> input;

        if (isValidInt(input, number)) {
            return number;
        }
        else {
			this->color.red();
			cerr << "Invalid input. Please enter a valid positive integer." << endl;
			this->color.reset();
            cout << "Try again      : ";
        }
    }
}


int GlobalConfig::getValidMaxTime(unsigned int minTime)
{
	unsigned int maxTime;

	while (true) {
		maxTime = getValidInt();

		if (maxTime <= minTime) {
			this->color.red();
            cerr << "Error: Maximum time must be greater than minimum time." << endl;
			this->color.reset();
            cout << "Try again      : ";
		}
		else {
			return maxTime;
		}
	}
}


int GlobalConfig::computeMaxParties(int tanks, int healers, int dps)
{
    int dpsParties = dps / 3;

    return std::min(std::min(tanks, healers), dpsParties);
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
	this->color.blue();
    cout << "[SYSTEM] LFG Configuration" << endl;
    cout << "------------------------" << endl;
    cout << "Maximum number of concurrent instances     : " << this->partyQueueConfig.n << endl;
    cout << "Number of tank players in the queue        : " << this->partyQueueConfig.t << endl;
    cout << "Number of healer players in the queue      : " << this->partyQueueConfig.h << endl;
    cout << "Number of DPS players in the queue         : " << this->partyQueueConfig.d << endl;
    cout << "Minimum time before an instance is finished: " << this->partyQueueConfig.t1 << endl;
    cout << "Maximum time before an instance is finished: " << this->partyQueueConfig.t2 << endl;
	cout << "Maximum number of parties formed           : " << this->maxNumParties << endl;
	cout << "------------------------" << endl;
	this->color.reset();
    cout << endl;
}
