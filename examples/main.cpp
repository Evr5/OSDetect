#include "os_detect/OSDetect.h"
#include <iostream>

int main() {
    OSDetect::OS OS = OSDetect::getOS();
    std::cout << "Detected OS: " << OS << std::endl;

    switch (OS) {
        case OSDetect::OS::Windows:
            std::cout << "Windows Version: " << OSDetect::getWindowsVersion() << std::endl;
            break;
        case OSDetect::OS::MacOS:
            std::cout << "MacOS Version: " << OSDetect::getMacOSVersion() << std::endl;
            break;
        case OSDetect::OS::Linux:
            std::cout << "Linux Distro: " << OSDetect::getLinuxDistro() << std::endl;
            break;
        default:
            std::cout << "Unknown Version" << std::endl;
    }
    return 0;
}
