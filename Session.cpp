//
// Created by kate on 01.10.2019.
//

#include "Session.h"
#include "Server.h"

//void Session::Handle(boost::asio::ip::tcp::socket socket) {
//    try {
//        for (;;) {
//            boost::asio::streambuf input_buffer;
//            boost::system::error_code ec;
//            auto s = boost::asio::read_until(socket, input_buffer, '\n', ec);
//            std::string str((std::istreambuf_iterator<char>(&input_buffer)), std::istreambuf_iterator<char>());
//
//            Request request;
//            request.Parse(str);
//
//            //TODO check
////            Response response(config.document_root_debug, request.url);//, map);
//            Response response(config.document_root, request.url);//, map);
//
//            std::string response_str;
//
//
//            if (!ec || ec == boost::asio::error::eof) {
//                if (!request.correct_request)
//                {
//                    response_str = response.Not_Alloved();
//                }
//
//                if (request.method == "GET")
//                {
//                    response_str = response.Get_Response();
//                }
//                if (request.method == "HEAD")
//                {
//                    response_str = response.Head_Response();
//                }
//
//                boost::system::error_code ignored_error;
//                int bytes_send = boost::asio::write(socket, boost::asio::buffer(response_str),
//                                                    boost::asio::transfer_all(), ignored_error);
//            }
//            break;
//        }
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << "Exception in thread: " << e.what() << "\n";
//    }
//}
