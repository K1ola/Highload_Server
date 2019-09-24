//
// Created by root on 22.09.2019.
//

#ifndef HIGHLOAD_DZ1_SERVER_H
#define HIGHLOAD_DZ1_SERVER_H


#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
//#include <unordered_map>
#include "Request.h"
#include "Response.h"
#include "Config.h"


#include "boost/filesystem.hpp"   // includes all needed Boost.Filesystem declarations
#include <iostream>               // for std::cout
using namespace boost::filesystem;

using boost::asio::ip::tcp;

class Server
{
public:
    Server() { config.ReadConfig(); };//getFilesToHashMap(); };
    Server(unsigned short _port)
            : port(_port) { config.ReadConfig(); };//getFilesToHashMap(); };
    void Start(boost::asio::io_service& io_service);
    Config config;
private:
    unsigned short port = 80;
    //void session(boost::asio::ip::tcp::socket);
//    void getFilesToHashMap();
//    void find_file(const boost::filesystem::path& dir_path);
//
//    std::unordered_map<std::string, std::string> map;
};


#endif //HIGHLOAD_DZ1_SERVER_H
