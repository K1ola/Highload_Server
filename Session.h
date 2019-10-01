//
// Created by kate on 01.10.2019.
//

#ifndef HIGHLOAD_DZ1_SESSION_H
#define HIGHLOAD_DZ1_SESSION_H

#include <boost/asio.hpp>
#include "Config.h"
#include <boost/enable_shared_from_this.hpp>

class Session
{
public:
    Session(Session&) = delete;
    Session(boost::asio::io_service &ioService)
    : Socket(ioService) {};
    boost::asio::ip::tcp::socket& GetSocket() { return Socket; }

private:
    boost::asio::ip::tcp::socket Socket;
};


#endif //HIGHLOAD_DZ1_SESSION_H
