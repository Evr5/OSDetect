#include "os_detect/OSDetect.h"

namespace OSDetect {

    OS getOS() {
    #if defined(_WIN32) || defined(_WIN64)
        return OS::Windows;
    #elif defined(__APPLE__) || defined(__MACH__)
        return OS::MacOS;
    #elif defined(__linux__)
        return OS::Linux;
    #else
        return OS::Unknown;
    #endif
    }

    std::string getOSName() {
        switch(getOS()) {
            case OS::Windows: return "Windows";
            case OS::MacOS:   return "MacOS";
            case OS::Linux:   return "Linux";
            default:          return "Unknown";
        }
    }

}
