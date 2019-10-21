#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Server.h"

int main()
{
    //TODO
    unsigned short port = 80;
//    unsigned short port = 8081;
    Server server(port, 180);    // 20 - 630rps, 200 - 540rps, 1 - 500rps
    try
    {
        server.Start();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }


    return 0;
}