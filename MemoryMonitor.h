#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <string>

class MemoryMonitor {
public:
    // Constructor
    MemoryMonitor();
    
    // Main function to get memory info
    void getMemoryInfo(unsigned long& totalMem, unsigned long& freeMem, unsigned long& availableMem);
    
    // Display memory information
    void displayMemoryInfo();
    
    // Get memory usage percentage
    double getMemoryUsage();
    
    // Get formatted memory string
    std::string getMemoryStatus();
};

#endif