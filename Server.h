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
#include "Session.h"
#include "ThreadPool.h"


#include "boost/filesystem.hpp"
#include <iostream>
#include <boost/thread.hpp>
#include <unordered_map>

using namespace boost::filesystem;

using boost::asio::ip::tcp;

class Server
          : public ThreadPool< boost::shared_ptr<Session> >
{
public:
    typedef boost::shared_ptr<Session> SessionPtr;
    //Server() {}//{ config.ReadConfig(); };//getFilesToHashMap(); };
    Server(unsigned short _port, int _threadsCount = 0)
            : Acceptor(IoService, tcp::endpoint(tcp::v4(), _port))
            , port(_port),
              ThreadPool::ThreadPool(_threadsCount) { config.ReadConfig(); getFilesToHashMap(); };
    void Start();
    void RunTask(boost::shared_ptr<Session> session);

private:
    Config config;
    unsigned short port = 80;
//    void session(boost::asio::ip::tcp::socket);
    boost::asio::io_service IoService;
    boost::asio::ip::tcp::acceptor Acceptor;


    SessionPtr NewSession;

//    typedef boost::shared_ptr<boost::thread> ThreadPtr;
//    typedef std::vector<ThreadPtr> ThreadPool;

    //ThreadPool< std::function<void()> > Threads;

    void getFilesToHashMap();
    void find_file(const boost::filesystem::path& dir_path);

    std::unordered_map<std::string, std::string> map;
};


#endif //HIGHLOAD_DZ1_SERVER_H
