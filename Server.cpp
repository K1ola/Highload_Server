#include "Server.h"
//#include <fstream>
#include <ctime>
//#include <sstream>
#include <string>
#include <iostream>

void Server::RunTask(boost::shared_ptr<Session> session) {
    try {
//        for (;;) {
            boost::asio::streambuf input_buffer;
            boost::system::error_code ec;
            auto s = boost::asio::read_until(session->GetSocket(), input_buffer, "\n", ec);
            std::string str((std::istreambuf_iterator<char>(&input_buffer)), std::istreambuf_iterator<char>());

            Request request;
            request.Parse(str);

            //TODO check
//            Response response(config.document_root_debug, request.url, map);
            Response response(config.document_root, request.url, map);

            std::string response_str;


            if (!ec || ec == boost::asio::error::eof) {
                if (!request.correct_request)
                {
                    response_str = response.Not_Alloved();
                }

                if (request.method == "GET")
                {
                    response_str = response.Get_Response();
                }
                if (request.method == "HEAD")
                {
                    response_str = response.Head_Response();
                }

                boost::system::error_code ignored_error;
                int bytes_send = boost::asio::write(session->GetSocket(), boost::asio::buffer(response_str),
                                                    boost::asio::transfer_all(), ignored_error);
//            }
//            break;
        }
    }
    catch (...)
    {
    }
    session->GetSocket().close();
}



void Server::Start()
{
    for (;;)
    {
        NewSession = boost::shared_ptr<Session>(new Session(IoService));
        Acceptor.accept(NewSession->GetSocket());
        AddTask(NewSession);
    }
}


void Server::getFilesToHashMap() {
    //TODO check
    const boost::filesystem::path& dir_path(config.document_root + "/httptest");
//    const boost::filesystem::path& dir_path(config.document_root_debug + "/httptest");
    find_file(dir_path);
}

void Server::find_file(const boost::filesystem::path& p)
{
    try
    {
        if (exists(p))    // does p actually exist?
        {
            directory_iterator end_itr;

            // cycle through the directory
            for (directory_iterator itr(p); itr != end_itr; ++itr)
            {
                // If it's not a directory, list it. If you want to list directories too, just remove this check.
                if (is_regular_file(itr->path())) {
                    // assign current file name to current_file and echo it out to the console.
                    std::string current_file = itr->path().string();
                    std::ifstream file(current_file, std::ios::binary);
                    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                    map[current_file] = content;
                   // std::cout << current_file << std::endl;
                }
                else
                {
                    find_file(itr->path());
                }
            }
        }
        else
            std::cout << p << " does not exist\n";
    }

    catch (const filesystem_error& ex)
    {
        std::cout << ex.what() << '\n';
    }
}
