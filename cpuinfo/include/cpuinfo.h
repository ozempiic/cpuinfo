#pragma once

#include <array>
#include <string>

std::string getCPUName();
bool isSingleCPU();
bool isHyperThreading();
std::string getCPUVendor();
std::string getCPUModel();
void getCpuCacheInfo(std::string& cacheInfo);
