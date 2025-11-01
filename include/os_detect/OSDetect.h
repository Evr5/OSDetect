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
        Tahoe,
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
        NixOS,
        Unknown
    };

    /**
     * @brief Return the basic os where the program is running. Linux, macOS or Windows
     * 
     * @return OS the os where the program is running
     */
    OS getOS();

    /**
     * @brief Get the Windows Version object
     * 
     * @return WindowsVersion 
     */
    WindowsVersion getWindowsVersion();
    /**
     * @brief Get the MacOS Version object
     * 
     * @return MacOSVersion 
     */
    MacOSVersion getMacOSVersion();
    /**
     * @brief Get the Linux Distro object
     * 
     * @return LinuxDistro 
     */
    LinuxDistro getLinuxDistro();

    /**
     * @brief Get the Detailed OS object, more specific
     * 
     * @tparam T 
     * @return T 
     */
    template <typename T>
    T getDetailedOS();

    // ------------------------------
    // Flow operator overload (<<)
    // ------------------------------
    std::ostream& operator<<(std::ostream& os, OSDetect::OS value);
    std::ostream& operator<<(std::ostream& os, OSDetect::WindowsVersion value);
    std::ostream& operator<<(std::ostream& os, OSDetect::MacOSVersion value);
    std::ostream& operator<<(std::ostream& os, OSDetect::LinuxDistro value);

}
