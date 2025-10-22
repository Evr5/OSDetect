#include <iostream>
#include "os_detect/OSDetect.h"

int main() {
    std::cout << "Detected OS: " << OSDetect::getOSName() << std::endl;
    return 0;
}
