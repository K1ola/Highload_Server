#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Server.h"

int main()
{
    unsigned short port = 8081;
    Server server(port);
    try
    {
        boost::asio::io_service io_service;

        server.Start(io_service);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }


    return 0;
}