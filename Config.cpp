#include <cstring>
#include <fstream>
#include "Config.h"
#include <unistd.h>

void Config::ReadConfig() {
    std::string full_path = CurrentPath() + "/../" +  config_path;
    std::ifstream conf_file_stream(full_path);

    if (conf_file_stream.is_open()) {
        std::string content((std::istreambuf_iterator<char>(conf_file_stream)), std::istreambuf_iterator<char>());

        auto cpu_limit_pos = content.find("cpu_limit");
        if (cpu_limit_pos != std::string::npos)
        {
            cpu_limit = std::atoi(content.substr(cpu_limit_pos + std::string("cpu_limit").size() + 1).c_str());
        }

        auto document_root_pos = content.find("document_root");
        if (document_root_pos != std::string::npos)
        {
            document_root = content.substr(document_root_pos + std::string(document_root).size() + 1);
        }

        auto thread_limit_pos = content.find("thread_limit");
        if (thread_limit_pos != std::string::npos) {
            thread_limit = std::atoi(content.substr(thread_limit_pos + std::string("thread_limit").size() + 1).c_str());
        }

        auto document_root_debug_pos = content.find("document_root_debug");
        if (thread_limit_pos != std::string::npos) {
            document_root_debug = content.substr(document_root_debug_pos + std::string("document_root_debug").size() + 1);
        }

    }
    conf_file_stream.close();
}

std::string Config::CurrentPath() {
    const unsigned short MAX_PATH = 1024;
    char buff[MAX_PATH];
    getcwd(buff, sizeof(buff));
    return std::string(buff);
}
