#ifndef HIGHLOAD_DZ1_CONFIG_H
#define HIGHLOAD_DZ1_CONFIG_H

#include <string>

class Config {
public:
    unsigned short port = 8887;
    unsigned short thread_limit = 256;
    std::string document_root = "/var/www/html";
    std::string config_path = "httpd.conf";
    unsigned short cpu_limit = 4;
public:
    Config() = default;
    void ReadConfig();
private:
    std::string current_path();
};


#endif //HIGHLOAD_DZ1_CONFIG_H
