#include "Server.h"
#include <fstream>
#include <ctime>
#include <sstream>


void Server::session(boost::asio::ip::tcp::socket socket)
{

}


void Server::Start(boost::asio::io_service& io_service)
{
    try
    {
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::asio::streambuf input_buffer;
            auto s = boost::asio::read_until(socket, input_buffer, '\n\n');
            std::string str((std::istreambuf_iterator<char>(&input_buffer)), std::istreambuf_iterator<char>());

            Request request;
            request.Parse(str);

            Response response(config.document_root_debug, request.url);

            std::string response_str;

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
            size_t request_length = response_str.size();
            auto buffer = boost::asio::buffer(response_str, request_length);

            //std::string sss(boost::asio::buffer_cast<const char*>(buffer), request_length);


            //std::cout << sss.c_str() << std::endl;

            int bytes_send = boost::asio::write(socket, buffer);
            socket.close();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

