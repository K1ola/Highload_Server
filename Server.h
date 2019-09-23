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
#include "Request.h"
#include "Response.h"
#include "Config.h"

using boost::asio::ip::tcp;

class Server
{
public:
    Server() { config.ReadConfig(); };
    Server(unsigned short _port)
            : port(_port) { config.ReadConfig(); };
    void Start(boost::asio::io_service& io_service);
    Config config;
private:
    unsigned short port = 80;
    void session(boost::asio::ip::tcp::socket);
};


#endif //HIGHLOAD_DZ1_SERVER_H
