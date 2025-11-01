#pragma once
#include <string>

namespace OSDetect {

    enum class OS {
        Windows,
        MacOS,
        Linux,
        Unknown
    };

    enum class WindowsVersion {
        Windows7,
        Windows8,
        Windows10,
        Windows11,
        Older,
        Unknown
    };

    enum class MacOSVersion {
        Catalina,
        BigSur,  
        Monterey,
        Ventura, 
        Sonoma,  
        Sequoia, 
        Older,
        Unknown
    };

    enum class LinuxDistro {
        Ubuntu,
        Debian,
        Fedora,
        Arch,
        OpenSUSE,
        Manjaro,
        CentOS,
        RedHat,
        Alpine,
        Unknown
    };

    OS getOS();

    WindowsVersion getWindowsVersion();
    MacOSVersion getMacOSVersion();
    LinuxDistro getLinuxDistro();

    // --- Interface générique basée sur template ---
    template <typename T>
    T getDetailedOS();

    std::ostream& operator<<(std::ostream& os, OSDetect::OS value);
    std::ostream& operator<<(std::ostream& os, OSDetect::WindowsVersion value);
    std::ostream& operator<<(std::ostream& os, OSDetect::MacOSVersion value);
    std::ostream& operator<<(std::ostream& os, OSDetect::LinuxDistro value);

}
