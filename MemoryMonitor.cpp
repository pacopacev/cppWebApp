#include "MemoryMonitor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>
#include <iomanip>

using namespace std;

MemoryMonitor::MemoryMonitor() {
    // Constructor can initialize if needed
}

void MemoryMonitor::getMemoryInfo(unsigned long& totalMem, unsigned long& freeMem, unsigned long& availableMem) {
    ifstream meminfo("/proc/meminfo");
    string line;
    
    while (getline(meminfo, line)) {
        if (line.find("MemTotal:") == 0) {
            sscanf(line.c_str(), "MemTotal: %lu kB", &totalMem);
        } else if (line.find("MemFree:") == 0) {
            sscanf(line.c_str(), "MemFree: %lu kB", &freeMem);
        } else if (line.find("MemAvailable:") == 0) {
            sscanf(line.c_str(), "MemAvailable: %lu kB", &availableMem);
        }
    }
    meminfo.close();
}

void MemoryMonitor::displayMemoryInfo() {
    unsigned long totalMem, freeMem, availableMem;
    
    getMemoryInfo(totalMem, freeMem, availableMem);
    
    cout << "=== RAM Memory Information (Linux) ===" << endl;
    cout << "Total RAM: " << totalMem / 1024 << " MB" << endl;
    cout << "Free RAM: " << freeMem / 1024 << " MB" << endl;
    cout << "Available RAM: " << availableMem / 1024 << " MB" << endl;
    cout << "Used RAM: " << (totalMem - availableMem) / 1024 << " MB" << endl;
    
    double usagePercent = ((totalMem - availableMem) * 100.0) / totalMem;
    cout << "Memory Usage: " << usagePercent << "%" << endl;
}

double MemoryMonitor::getMemoryUsage() {
    unsigned long totalMem, freeMem, availableMem;
    getMemoryInfo(totalMem, freeMem, availableMem);
    return ((totalMem - availableMem) * 100.0) / totalMem;
}

string MemoryMonitor::getMemoryStatus() {
    unsigned long totalMem, freeMem, availableMem;
    getMemoryInfo(totalMem, freeMem, availableMem);
    
    stringstream ss;
    ss << fixed << setprecision(1);
    ss << "Memory: " << ((totalMem - availableMem) * 100.0) / totalMem << "% used ";
    ss << "(" << (totalMem - availableMem) / 1024 << "MB/" << totalMem / 1024 << "MB)";
    
    return ss.str();
}