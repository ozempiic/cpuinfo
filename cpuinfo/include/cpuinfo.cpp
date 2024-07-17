#include "cpuinfo.h"
#include <Windows.h>
#include <cpuid.h>

using namespace std;


// gets cpu name
string getCPUName() {
    array<int, 4> cpui;
    array<int, 4> namePart1, namePart2, namePart3;

    __cpuid(0x80000000, cpui[0], cpui[1], cpui[2], cpui[3]);
    if (cpui[0] >= 0x80000004) {
        __cpuid(0x80000002, namePart1[0], namePart1[1], namePart1[2], namePart1[3]);
        __cpuid(0x80000003, namePart2[0], namePart2[1], namePart2[2], namePart2[3]);
        __cpuid(0x80000004, namePart3[0], namePart3[1], namePart3[2], namePart3[3]);
    }

    char name[49]; // fixed size buffer
    memcpy(name, namePart1.data(), 16);
    memcpy(name + 16, namePart2.data(), 16);
    memcpy(name + 32, namePart3.data(), 16);
    name[48] = '\0'; // string termination manually set

    return std::string(name);
}

// checks if it has 1 or more cores
bool isSingleCPU() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return (sysInfo.dwNumberOfProcessors == 1);
}


// checks if hyperthreading is enabled
bool isHyperThreading() {
    std::array<int, 4> cpui;
    __cpuid(1, cpui[0], cpui[1], cpui[2], cpui[3]);
    return cpui[3] & (1 << 28);
}

// grabs cpu vendor name
std::string getCPUVendor() {
    std::array<int, 4> cpui;
    __cpuid(0, cpui[0], cpui[1], cpui[2], cpui[3]);
    char vendor[13];
    memcpy(vendor, &cpui[1], 4);
    memcpy(vendor + 4, &cpui[3], 4);
    memcpy(vendor + 8, &cpui[2], 4);
    vendor[12] = '\0';
    return std::string(vendor);
}

// grabs cpu model name
std::string getCPUModel() {
    std::array<int, 4> cpui;
    __cpuid(1, cpui[0], cpui[1], cpui[2], cpui[3]);
    int family = (cpui[0] >> 8) & 0xf;
    int model = (cpui[0] >> 4) & 0xf;
    int stepping = cpui[0] & 0xf;
    return "Family " + std::to_string(family) + ", Model " + std::to_string(model) + ", Stepping " + std::to_string(stepping);
}

// grabs cpu cache info
void getCpuCacheInfo(std::string& cacheInfo) {
    int cacheLevel = 0;

    while (true) {
        unsigned int cpui[4];
        __cpuid_count(4, cacheLevel, cpui[0], cpui[1], cpui[2], cpui[3]);

        int type = (cpui[0] & 0x1F);
        if (type == 0) break;

        int cacheSize = ((cpui[1] & 0xFFFF) * 1024) + 1;
        int cacheSets = ((cpui[1] >> 16) & 0xFFFF) + 1;
        int associativity = ((cpui[2] & 0xFF) + 1) * ((cpui[2] >> 12 & 0xFF) + 1);
        int lineSize = (cpui[1] & 0xFFF) + 1;

        cacheInfo += "Level " + std::to_string(cacheLevel) + " Cache:\n";
        cacheInfo += "Type: " + std::to_string(type) + "\n";
        cacheInfo += "Size: " + std::to_string(cacheSize) + " KB\n";
        cacheInfo += "Sets: " + std::to_string(cacheSets) + "\n";
        cacheInfo += "Associativity: " + std::to_string(associativity) + "\n";
        cacheInfo += "Line Size: " + std::to_string(lineSize) + " bytes\n\n";

        cacheLevel++;
    }
}
