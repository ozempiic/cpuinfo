#include <iostream>
#include <string>
#include "cpuinfo.h"

using namespace std;

// main func that calls all other funcs
int main() {
    string cpuName = getCPUName();
    string cpuVendor = getCPUVendor();
    string cpuModel = getCPUModel();
    bool singleCPU = isSingleCPU();
    bool hyperThreading = isHyperThreading();
    string cacheInfo;

    getCpuCacheInfo(cacheInfo);

    cout << "CPU Vendor: " << cpuVendor << "\n";
    cout << "CPU Model: " << cpuModel << "\n";
    cout << "CPU Name: " << cpuName << "\n";
    cout << "Number of Processors: " << (singleCPU ? "Only one CPU detected." : "More than one CPU detected.") << "\n";
    cout << "Hyper-Threading: " << (hyperThreading ? "Enabled" : "Disabled") << "\n\n";
    cout << "Cache Information:\n" << cacheInfo;

    return 0;
}
