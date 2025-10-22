#pragma once
#include <string>

namespace OSDetect {

    enum class OS {
        Windows,
        MacOS,
        Linux,
        Unknown
    };

    OS getOS();
    std::string getOSName();

}
