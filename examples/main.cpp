#include "os_detect/OSDetect.h"
#include <iostream>

int main() {
    OSDetect::OS OS = OSDetect::getOS();

    std::cout << "Detected OS: " << OS << std::endl;

    switch (OS) {
        case OSDetect::OS::Windows:
            std::cout << "Version: " << OSDetect::getWindowsVersion() << "\n";
            break;
        case OSDetect::OS::MacOS:
            std::cout << "Version: " << OSDetect::getMacOSVersion() << "\n";
            break;
        case OSDetect::OS::Linux:
            std::cout << "Distro: " << OSDetect::getLinuxDistro() << "\n";
            break;
        default:
            std::cout << "Version inconnue\n";
    }

    return 0;
}
