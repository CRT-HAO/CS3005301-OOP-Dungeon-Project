#pragma once

#if defined __APPLE__
#include <mach-o/dyld.h>
#elif defined _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace Dungeon
{

    class File
    {
    public:
        static std::filesystem::path getExeDirectory()
        {
#if defined __APPLE__
            // MacOS specific
            char szPath[PATH_MAX];
            uint32_t size = sizeof(szPath);
            _NSGetExecutablePath(szPath, &size);
#elif defined _WIN32
            // Windows specific
            wchar_t szPath[MAX_PATH];
            GetModuleFileNameW(NULL, szPath, MAX_PATH);
#else
            // Linux specific
            char szPath[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", szPath, PATH_MAX);
            if ( count < 0 || count >= PATH_MAX )
                return {}; // some error
            szPath[count] = '\0';
#endif
            // to finish the folder path with (back)slash
            return std::filesystem::path{szPath}.parent_path() / "";
        }

        static fs::path getResPath()
        {
            fs::path p;
            p /= File::getExeDirectory().u8string();
#if defined __APPLE__
            p /= "../Resources/resources/";
#else
            p /= "resources/";
#endif
            return p;
        }
    };

}