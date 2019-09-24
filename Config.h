#ifndef HIGHLOAD_DZ1_CONFIG_H
#define HIGHLOAD_DZ1_CONFIG_H

#include <string>

class Config {
public:
    unsigned short port = 8887;
    unsigned short thread_limit = 256;
    std::string document_root = "/var/www/html";
    std::string config_path = "httpd.conf";
    std::string document_root_debug = "/home/kate/CLionProjects/Highload_Server";
    unsigned short cpu_limit = 4;
public:
    Config() = default;
    void ReadConfig();
    std::string CurrentPath();
private:
	std::string GetValue(std::string content, std::string key);
};


#endif //HIGHLOAD_DZ1_CONFIG_H
