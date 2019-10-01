#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Server.h"

int main()
{
    unsigned short port = 80;
    Server server(port);
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