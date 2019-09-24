#include <cstring>
#include <fstream>
#include "Config.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string Config::GetValue(std::string content, std::string key)
{
	auto beg_pos = content.find(key);
	if (beg_pos == std::string::npos) return "";
	beg_pos += key.size();
	auto end_pos = content.find_first_of("#\r\n", beg_pos);
	if (end_pos == std::string::npos) end_pos = content.length();
	std::string item = content.substr(beg_pos, end_pos-beg_pos);
	auto space_pos = item.find_first_not_of(" ");
	if (space_pos != std::string::npos) item = item.erase(0, space_pos);
	while (item.back() == ' ') item.pop_back();
	return item;
}

void Config::ReadConfig() {
    std::string full_path = CurrentPath() + "/../" +  config_path;
    std::ifstream conf_file_stream(full_path);

    if (conf_file_stream.is_open()) {
        std::string content((std::istreambuf_iterator<char>(conf_file_stream)), std::istreambuf_iterator<char>());

        std::string value = GetValue(content, "cpu_limit");
		if (!value.empty()) cpu_limit = std::stoi(value);

		value = GetValue(content, "document_root");
		if (!value.empty()) document_root = value;

        value = GetValue(content, "thread_limit");
        if (!value.empty()) thread_limit = std::stoi(value);

        value = GetValue(content, "debug_document_root");
        if (!value.empty()) document_root_debug = value;
    }
    conf_file_stream.close();
}

std::string Config::CurrentPath() {
#ifndef _WIN32
	const unsigned short MAX_PATH = 1024;
#endif
    char buff[MAX_PATH];
#ifdef _WIN32
	GetCurrentDirectoryA(sizeof(buff), buff);
#else
	getcwd(buff, sizeof(buff));
#endif
	return std::string(buff);
}
