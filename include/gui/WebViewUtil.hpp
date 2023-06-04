/**
 *  File: WebViewUtil.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 11:07:41
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 11:20:15
 *  Description: WebView Utility
 */

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

    class WebViewUtil
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

        static std::string getLocalPath(const std::string &path)
        {
            std::string p = "file:///";
            p += WebViewUtil::getExeDirectory().u8string();
#if defined __APPLE__
            p += "../Resources/assets/";
#else
            p += "assets/";
#endif
            p += path;
            return p;
        }
    };

}