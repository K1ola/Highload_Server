#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Request.h"
#include "Response.h"

using boost::asio::ip::tcp;

int main()
{
	setlocale(LC_ALL, "Russian");
	unsigned short port = 8888;
	try
	{
		boost::asio::io_service io_service;

		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

		for (;;)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			// works
			//char data[1024];
			boost::system::error_code ec;
			//auto buffer = boost::asio::buffer(data);
			//size_t s = socket.receive(buffer);
			// end works

			boost::asio::streambuf buffer;
			auto s = boost::asio::read_until(socket, buffer, '\n\n');
			std::string str((std::istreambuf_iterator<char>(&buffer)), std::istreambuf_iterator<char>());
	
			Request request;
			request.Parse(str);

			Response response(request.url);

			//unsigned char* p1 = static_cast<unsigned char*>(buffer.data());
			//std::cout << p1 << std::endl;

			if (!ec || ec == boost::asio::error::eof) {
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
				int bytes_send = boost::asio::write(socket, boost::asio::buffer(response_str),
				boost::asio::transfer_all(), ignored_error);
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}



/////////////////////////////////////////
//#include "Server.h"
//
//#include <cstdlib>
//#include <iostream>
//#include <thread>
//#include <utility>
//#include <boost/asio.hpp>
//
//using boost::asio::ip::tcp;
//
//const int max_length = 1024;
//
//void session(tcp::socket socket)
//{
//	try
//	{
//		while (true)
//		{
//			char data[max_length];
//
//			boost::system::error_code error;
//
//
//			//boost::asio::streambuf request;
//			//boost::asio::read_until(socket, request, "\n\n");
//			//size_t length1 = request.size();
//
//			//size_t length = socket.read_some(boost::asio::buffer(data), error);
//
//			bool flag = error == boost::asio::error::eof;
//			if (flag)
//			{
//				break; // Connection closed cleanly by peer.
//			}
//			if (error)
//				throw boost::system::system_error(error); // Some other error.
//
//
//			//auto buffer = boost::asio::buffer(data, length);
//			//unsigned char* p1 = static_cast<unsigned char*>(buffer.data());
//			//std::cout << p1 << std::endl;
//			//bool result = boost::asio::write(socket, buffer);
//
//				// Данные успешно получены
//			char response[max_length];
//
//			// Формируем весь ответ вместе с заголовками
//			strcpy_s(response, "HTTP/1.1 200 OK\r\n Version: HTTP/1.1\r\n Content-Type: text/html; charset=utf-8\r\n Content-Length: 78 \r\n\r\n");
//
//			int bytes_send = socket.write_some(boost::asio::buffer(response, 78));
//			std::cout << bytes_send << std::endl;
//		}	
//	}
//	catch (std::exception& e)
//	{
//		std::cerr << "Exception in thread: " << e.what() << "\n";
//	}
//}
//
//void server(boost::asio::io_service& io_service, unsigned short port)
//{
//	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
//	while (true) 
//	{
//		std::thread(session, acceptor.accept()).detach();
//	}
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	unsigned short port = 8888;
//	try
//	{
//		boost::asio::io_service io_service;
//
//		std::cout << "Started server" << std::endl;
//		server(io_service, port);
//	}
//	catch (std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << "\n";
//	}
//
//
//	return 0;
//}
