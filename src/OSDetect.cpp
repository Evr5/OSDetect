#include "os_detect/OSDetect.h"
#include <string>
#include <fstream>

#if defined(_WIN32)
    #include <windows.h>
    #include <versionhelpers.h>
#elif defined(__APPLE__) || defined(__MACH__)
    #include <sys/utsname.h>
#elif defined(__linux__)
    #include <sys/utsname.h>
#endif

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

    // ------------------------------
    // Windows
    // ------------------------------
    WindowsVersion getWindowsVersion() {
        #if defined(_WIN32)
            if (IsWindows10OrGreater()) return WindowsVersion::Windows10;
            if (IsWindows8OrGreater())  return WindowsVersion::Windows8;
            if (IsWindows7OrGreater())  return WindowsVersion::Windows7;
            return WindowsVersion::Older;
        #else
            return WindowsVersion::Unknown;
        #endif
    }

    // ------------------------------
    // macOS
    // ------------------------------
    MacOSVersion getMacOSVersion() {
        #if defined(__APPLE__) || defined(__MACH__)
            struct utsname buffer;
            if (uname(&buffer) == 0) {
                std::string rel = buffer.release;
                int major = std::stoi(rel.substr(0, rel.find('.')));
                switch (major) {
                    case 19: return MacOSVersion::Catalina;
                    case 20: return MacOSVersion::BigSur;
                    case 21: return MacOSVersion::Monterey;
                    case 22: return MacOSVersion::Ventura;
                    case 23: return MacOSVersion::Sonoma;
                    case 24: return MacOSVersion::Sequoia;
                    case 25: return MacOSVersion::Tahoe
                    default: return MacOSVersion::Older;
                }
            }
            return MacOSVersion::Unknown;
        #else
            return MacOSVersion::Unknown;
        #endif
    }

    // ------------------------------
    // Linux
    // ------------------------------
    LinuxDistro getLinuxDistro() {
        #if defined(__linux__)
            std::ifstream file("/etc/os-release");
            if (file) {
                std::string line;
                while (std::getline(file, line)) {
                    if (line.find("ID=") == 0) {
                        std::string id = line.substr(3);
                        if (id == "ubuntu")  return LinuxDistro::Ubuntu;
                        if (id == "debian")  return LinuxDistro::Debian;
                        if (id == "fedora")  return LinuxDistro::Fedora;
                        if (id == "arch")    return LinuxDistro::Arch;
                        if (id == "opensuse")return LinuxDistro::OpenSUSE;
                        if (id == "manjaro") return LinuxDistro::Manjaro;
                        if (id == "centos")  return LinuxDistro::CentOS;
                        if (id == "rhel" || id == "redhat") return LinuxDistro::RedHat;
                        if (id == "alpine")  return LinuxDistro::Alpine;
                        if (id == "nixos")     return LinuxDistro::NixOS; 
                        return LinuxDistro::Unknown;
                    }
                }
            }
            return LinuxDistro::Unknown;
        #else
            return LinuxDistro::Unknown;
        #endif
    }

    // ------------------------------
    // Template
    // ------------------------------
    template <>
    WindowsVersion getDetailedOS<WindowsVersion>() {
        return getWindowsVersion();
    }

    template <>
    MacOSVersion getDetailedOS<MacOSVersion>() {
        return getMacOSVersion();
    }

    template <>
    LinuxDistro getDetailedOS<LinuxDistro>() {
        return getLinuxDistro();
    }

    // ------------------------------
    // Flow operator overload (<<)
    // ------------------------------
    std::ostream& operator<<(std::ostream& os, OS value) {
        switch (value) {
            case OS::Windows: return os << "Windows";
            case OS::MacOS:   return os << "macOS";
            case OS::Linux:   return os << "Linux";
            default:          return os << "Unknown OS";
        }
    }

    std::ostream& operator<<(std::ostream& os, WindowsVersion v) {
        switch (v) {
            case WindowsVersion::Windows7:  return os << "Windows 7";
            case WindowsVersion::Windows8:  return os << "Windows 8";
            case WindowsVersion::Windows10: return os << "Windows 10";
            case WindowsVersion::Windows11: return os << "Windows 11";
            case WindowsVersion::Older:     return os << "Older Windows";
            default:                        return os << "Unknown Windows Version";
        }
    }

    std::ostream& operator<<(std::ostream& os, MacOSVersion v) {
        switch (v) {
            case MacOSVersion::Catalina: return os << "macOS Catalina (10.15)";
            case MacOSVersion::BigSur:   return os << "macOS Big Sur (11)";
            case MacOSVersion::Monterey: return os << "macOS Monterey (12)";
            case MacOSVersion::Ventura:  return os << "macOS Ventura (13)";
            case MacOSVersion::Sonoma:   return os << "macOS Sonoma (14)";
            case MacOSVersion::Sequoia:  return os << "macOS Sequoia (15)";
            case MacOSVersion::Tahoe     return os << "macOS Tahoe (26)";
            case MacOSVersion::Older:    return os << "Older macOS";
            default:                     return os << "Unknown macOS Version";
        }
    }

    std::ostream& operator<<(std::ostream& os, LinuxDistro v) {
        switch (v) {
            case LinuxDistro::Ubuntu:   return os << "Ubuntu";
            case LinuxDistro::Debian:   return os << "Debian";
            case LinuxDistro::Fedora:   return os << "Fedora";
            case LinuxDistro::Arch:     return os << "Arch Linux";
            case LinuxDistro::OpenSUSE: return os << "openSUSE";
            case LinuxDistro::Manjaro:  return os << "Manjaro";
            case LinuxDistro::CentOS:   return os << "CentOS";
            case LinuxDistro::RedHat:   return os << "Red Hat";
            case LinuxDistro::Alpine:   return os << "Alpine Linux";
            case LinuxDistro::NixOS:    return os << "NixOS";
            default:                    return os << "Unknown Linux Distro";
        }
    }
}   
