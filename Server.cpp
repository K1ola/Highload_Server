#include "Server.h"
#include <ctime>
#include <string>
#include <iostream>

void Server::RunTask(boost::shared_ptr<Session> session) {
    try {
//        std::mutex m;
//        m.lock();
//        c++;
//        m.unlock();
            boost::asio::streambuf input_buffer;
            boost::system::error_code ec;
            size_t length = boost::asio::read_until(session->GetSocket(), input_buffer, "\n", ec);
            if (!input_buffer.size()) {
                std::cout << "Empty read socket" << std::endl;
                return;
            }
//            std::string str((std::istreambuf_iterator<char>(&input_buffer)), std::istreambuf_iterator<char>());
            auto data = input_buffer.data();
            std::string str (boost::asio::buffers_begin(data), boost::asio::buffers_begin(data) + length);

            if (str.empty()) {
                std::cout << "Empty str" << std::endl;
                return;
            }

            if (ec) {
                std::cout << "Exception: " << ec.message() << std::endl;
                throw boost::system::system_error(ec);
            }

            Request request;
            request.Parse(str);

            //TODO check
            Response response(config.document_root_debug, request.url, map);
//            Response response(config.document_root, request.url, map);
//
            std::string response_str;
//
//
//            if (!ec || ec == boost::asio::error::eof) {
                if (!request.correct_request)
                {
                    std::cout << "Bad_Request" << std::endl;
                    std::cout << str << std::endl;
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

//                boost::system::error_code error;
//                session->GetSocket().write_some(boost::asio::buffer(response_str), error);

                boost::system::error_code ignored_error;
                boost::asio::write(session->GetSocket(), boost::asio::buffer(response_str));
//                                                    boost::asio::transfer_all(), ignored_error);
//                //session->GetSocket().close();
//            } else {
//                std::cout << "Acceptor error" << std::endl;
//                return;
//            }
//        char data[1024];

//        boost::system::error_code error;
//        size_t length = session->GetSocket().read_some(boost::asio::buffer(data), error);
//        if (error == boost::asio::error::eof)
//            return; // Connection closed cleanly by peer.
//        else if (error)
//            throw boost::system::system_error(error); // Some other error.

//        const std::string data1("HTTP/1.0 200 OK\nDate: Sun Oct 20 17:37:17 2019\nServer: Highload Static Server\nContent-Length: 954824\nContent-Type: text/html\nConnection: Closed\n");

//        boost::asio::write(session->GetSocket(), boost::asio::buffer(data1));
    }
//
//    catch (std::exception& e)
//    {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
    catch (...)
    {
    }
    //session->GetSocket().close();
}



void Server::Start()
{
    for (;;)
    {
        NewSession = boost::shared_ptr<Session>(new Session(IoService));
        boost::system::error_code error;
//        Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        Acceptor.accept(NewSession->GetSocket(), error);
//        if (c >= 99990)
//            std::cout << "Counter " << c << std::endl;
//        if (!error) {
            AddTask(NewSession);
//        } else {
//            std::cout << "Acceptor error" << std::endl;
//        }
    }
}


void Server::getFilesToHashMap() {
    //TODO check
//    const boost::filesystem::path& dir_path(config.document_root + "/httptest");
    const boost::filesystem::path& dir_path(config.document_root_debug + "/httptest");
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

